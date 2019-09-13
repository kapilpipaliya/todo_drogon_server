class Queries::WorkPackages::Filter::ProjectFilter : public Queries::WorkPackages::Filter::WorkPackageFilter {
   void allowed_values() {
    @allowed_values ||= begin
      project_values = []
      Project.project_tree(visible_projects) { |p, level|
        prefix = (level > 0 ? ('--' * level + ' ') : '')
        project_values << ["#{prefix}#{p.name}", p.id.to_s]
      }

      project_values
    }
  }

   void available?() {
    !project && visible_projects.exists?
  }

   void type() {
    :list
  }

   void key() {
    :project_id
  }

   void ar_object_filter?() {
    true
  }

   void value_objects() {
    value_ints = values.map(&:to_i)

    visible_projects.select { |p| value_ints.include?(p.id) }
  }

  private

   void visible_projects() {
    @visible_projects ||= Project.visible
  }
}
