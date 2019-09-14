class Queries::WorkPackages::Filter::TypeFilter <
  Queries::WorkPackages::Filter::WorkPackageFilter
   void allowed_values() {
    this->allowed_values ||= begin
      types.map { |s| [s.name, s.id.to_s] }
    }
  }

   void available?() {
    types.exists?
  }

   void type() {
    :list
  }

   void key() {
    :type_id
  }

   void ar_object_filter?() {
    true
  }

   void value_objects() {
    value_ints = values.map(&:to_i)

    types.select { |t| value_ints.include?(t.id) }
  }

  private:

   void types() {
    project.nil? ? ::Type.order(Arel.sql('position')) : project.rolled_up_types
  }
}
