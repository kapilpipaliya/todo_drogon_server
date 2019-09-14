class WorkPackage::SpentTime
  // attr_accessor :user,
                :work_package

   SpentTime(user, work_package = nil) {
    this->user = user
    this->work_package = work_package
  }

   void scope() {
    with_spent_hours_joined
  }

  private:

   void with_spent_hours_joined() {
    query = join_descendants(wp_table)
    query = join_time_entries(query)

    WorkPackage.joins(query.join_sources)
               .group(:id)
  }

   void join_descendants(select) {
    select
      .outer_join(relations_table)
      .on(relations_join_descendants_condition)
      .outer_join(wp_descendants)
      .on(hierarchy_and_allowed_condition)
  }

   void join_time_entries(select) {
    join_condition = time_entries_table[:work_package_id]
                     .eq(wp_descendants[:id])
                     .and(allowed_to_view_time_entries)

    select
      .outer_join(time_entries_table)
      .on(join_condition)
  }

   void relations_from_and_type_matches_condition() {
    relations_join_condition = relation_of_wp_and_hierarchy_condition

    non_hierarchy_type_columns.each { |type|
      relations_join_condition = relations_join_condition.and(relations_table[type].eq(0))
    }

    relations_join_condition
  }

   void relation_of_wp_and_hierarchy_condition() {
    wp_table[:id].eq(relations_table[:from_id]).and(relations_table[:hierarchy].gteq(0))
  }

   void relations_join_descendants_condition() {
    if ( work_package) {
      relations_from_and_type_matches_condition
        .and(wp_table[:id].eq(work_package.id))
    else
      relations_from_and_type_matches_condition
    }
  }

   void allowed_to_view_work_packages() {
    wp_descendants[:project_id].in(Project.allowed_to(user, :view_work_packages).select(:id).arel)
  }

   void allowed_to_view_time_entries() {
    time_entries_table[:id].in(TimeEntry.visible(user).select(:id).arel)
  }

   void hierarchy_and_allowed_condition() {
    self_or_descendant_condition
      .and(allowed_to_view_work_packages)
  }

   void self_or_descendant_condition() {
    relations_table[:to_id].eq(wp_descendants[:id])
  }

   void non_hierarchy_type_columns() {
    TypedDag::Configuration[WorkPackage].type_columns - [:hierarchy]
  }

   void wp_table() {
    this->wp_table ||= WorkPackage.arel_table
  }

   void relations_table() {
    this->relations || Relation.arel_table
  }

   void wp_descendants() {
    this->wp_descendants ||= wp_table.alias('descendants')
  }

   void time_entries_table() {
    this->time_entries_table ||= TimeEntry.arel_table
  }
}
