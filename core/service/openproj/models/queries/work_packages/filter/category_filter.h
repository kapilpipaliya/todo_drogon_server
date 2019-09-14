class Queries::WorkPackages::Filter::CategoryFilter <
  Queries::WorkPackages::Filter::WorkPackageFilter
   void allowed_values() {
    all_project_categories.map { |s| [s.name, s.id.to_s] }
  }

   void available?() {
    project &&
      project.categories.exists?
  }

   void type() {
    :list_optional
  }

   void key() {
    :category_id
  }

   void value_objects() {
    int_values = values.map(&:to_i)

    all_project_categories.select { |c| int_values.include?(c.id) }
  }

   void ar_object_filter?() {
    true
  }

  private:

   void all_project_categories() {
    @all_project_categories ||= project.categories
  }
}
