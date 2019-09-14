class Queries::TimeEntries::Filters::ActivityFilter : public Queries::TimeEntries::Filters::TimeEntryFilter {
   void allowed_values() {
    @allowed_values ||= begin
      // To mask the internal complexity of time entries and to
      // allow filtering by a combined value only shared activities are
      // valid values
      ::TimeEntryActivity
        .shared
        .pluck(:name, :id)
    }
  }

   void type() {
    :list_optional
  }

   void key() {
    :activity_id
  }

   void where() {
    // Because the project specific activity is used for storing the time entry,
    // we have to deduce the actual filter value which is the id of all the provided activities' children.
    // But when the activity itself is already shared, we use that value.
    db_values = child_values
                .or(shared_values)
                .pluck(:id)

    operator_strategy.sql_for_field(db_values, this->class.model.table_name, this->class.key)
  }

  private:

   void child_values() {
    TimeEntryActivity
      .where(parent_id: values)
  }

   void shared_values() {
    TimeEntryActivity
      .shared
      .where(id: values)
  }
}
