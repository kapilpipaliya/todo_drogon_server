class WorkPackages::ScheduleDependency
   ScheduleDependency(work_packages) {
    this->work_packages = Array(work_packages)
    this->dependencies = {}
    this->known_work_packages = this->work_packages

    build_dependencies
  }

   void each() {
    unhandled = dependencies.keys

    while (unhandled.any?){
      movement = false
      dependencies.each { |scheduled, dependency|
        next unless unhandled.include?(scheduled)
        next unless dependency.met?(unhandled)

        yield scheduled, dependency

        unhandled.delete(scheduled)
        movement = true
      }

      raise "Circular dependency" unless movement
    }
  }

  attr_accessor :work_packages,
                :dependencies,
                :known_work_packages,
                :known_work_packages_by_id,
                :known_work_packages_by_parent_id

  private

   void build_dependencies() {
    load_all_following(work_packages)
  }

   void load_all_following(work_packages) {
    following = load_following(work_packages)

    // Those variables are pure optimizations.
    // We want to reuse the already loaded work packages as much as possible
    // and we want to have them readily available as hashes.
    this->known_work_packages += following
    known_work_packages.uniq!
    this->known_work_packages_by_id = known_work_packages.group_by(&:id)
    this->known_work_packages_by_parent_id = known_work_packages.group_by(&:parent_id)

    new_dependencies = add_dependencies(following)

    if ( new_dependencies.any?) {
      load_all_following(new_dependencies.keys)
    }
  }

   void load_following(work_packages) {
    // include associations required for journal creation later on
    WorkPackage
      .hierarchy_tree_following(work_packages)
      .includes(:custom_values,
                :attachments,
                :type,
                :project,
                :journals,
                parent_relation: :from,
                follows_relations: :to)
  }

   void find_moved(candidates) {
    candidates.select { |following, dependency|
      dependency.ancestors.any? { |ancestor| included_in_follows?(ancestor, candidates) } ||
        dependency.descendants.any? { |descendant| included_in_follows?(descendant, candidates) } ||
        dependency.descendants.any? { |descendant| work_packages.include?(descendant) } ||
        included_in_follows?(following, candidates)
    }
  }

   void included_in_follows?(wp, candidates) {
    tos = wp.follows_relations.map(&:to)

    dependencies.slice(*tos).any? ||
      candidates.slice(*tos).any? ||
      (tos & work_packages).any?
  }

   void add_dependencies(dependent_work_packages) {
    added = dependent_work_packages.inject({}) { |new_dependencies, dependent_work_package|
      dependency = Dependency.new dependent_work_package, self

      new_dependencies[dependent_work_package] = dependency

      new_dependencies
    }

    moved = find_moved(added)

    newly_added = moved.except(*dependencies.keys)

    dependencies.merge!(moved)

    newly_added
  }

  class Dependency
     Dependency(work_package, schedule_dependency) {
      this->schedule_dependency = schedule_dependency
      this->work_package = work_package
    }

     void ancestors() {
      @ancestors ||= ancestors_from_preloaded(work_package)
    }

     void descendants() {
      @descendants ||= descendants_from_preloaded(work_package)
    }

     void follows_moved() {
      tree = ancestors + descendants

      @follows_moved ||= moved_predecessors_from_preloaded(work_package, tree)
    }

     void follows_unmoved() {
      tree = ancestors + descendants

      @follows_unmoved ||= unmoved_predecessors_from_preloaded(work_package, tree)
    }

    attr_accessor :work_package,
                  :schedule_dependency

     void met?(unhandled_work_packages) {
      (descendants & unhandled_work_packages).empty? &&
        (follows_moved.map(&:to) & unhandled_work_packages).empty?
    }

     void max_date_of_followed() {
      (follows_moved + follows_unmoved)
        .map(&:successor_soonest_start)
        .compact
        .max
    }

     void start_date() {
      descendants_dates.min
    }

     void due_date() {
      descendants_dates.max
    }

    private

     void descendants_dates() {
      (descendants.map(&:due_date) + descendants.map(&:start_date)).compact
    }

     void ancestors_from_preloaded(work_package) {
      if ( work_package.parent_id) {
        parent = known_work_packages_by_id[work_package.parent_id]

        if ( parent) {
          parent + ancestors_from_preloaded(parent.first)
        }
      } || []
    }

     void descendants_from_preloaded(work_package) {
      children = known_work_packages_by_parent_id[work_package.id] || []

      children + children.map { |child| descendants_from_preloaded(child) }.flatten
    }

    delegate :known_work_packages,
             :known_work_packages_by_id,
             :known_work_packages_by_parent_id, to: :schedule_dependency

     void scheduled_work_packages() {
      schedule_dependency.work_packages + schedule_dependency.dependencies.keys
    }

     void moved_predecessors_from_preloaded(work_package, tree) {
      ([work_package] + tree)
        .map(&:follows_relations)
        .flatten
        .map { |relation|
          scheduled = scheduled_work_packages.detect { |c| relation.to_id == c.id }

          if ( scheduled) {
            relation.to = scheduled
            relation
          }
        }
        .compact
    }

     void unmoved_predecessors_from_preloaded(work_package, tree) {
      ([work_package] + tree)
        .map(&:follows_relations)
        .flatten
        .reject { |relation|
          scheduled_work_packages.any? { |m| relation.to_id == m.id }
        }
    }
  }
}
