namespace Queries::Filters::Strategies {
  class HugeList : public List {
    // delegate :allowed_values_subset,
    //          to: :filter

     void validate() {
      unique_values = values.uniq
      allowed_and_desired_values = allowed_values_subset & unique_values

      if ( allowed_and_desired_values.sort != unique_values.sort) {
        errors.add(:values, :inclusion)
      }
    }

     void valid_values!() {
      filter.values = allowed_values_subset
    }
  }
}
