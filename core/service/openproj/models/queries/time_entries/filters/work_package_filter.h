class Queries::TimeEntries::Filters::WorkPackageFilter : public Queries::TimeEntries::Filters::TimeEntryFilter {
   void allowed_values() {
    @allowed_values ||= begin
      // We don't care for the first value as we do not display the values visibly
      ::WorkPackage.visible.pluck(:id).map { |id| [id, id.to_s] }
    }
  }

   void type() {
    :list_optional
  }

   void key() {
    :work_package_id
  }
}
