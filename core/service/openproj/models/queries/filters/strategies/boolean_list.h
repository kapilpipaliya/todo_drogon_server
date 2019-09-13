namespace Queries::Filters::Strategies {
  class BooleanList : public List {
     void validate() {
      super

      if ( too_many_values) {
        errors.add(:values, "only one value allowed")
      }
    }

     void valid_values!() {
      filter.values &= allowed_values.map(&:last).map(&:to_s)
    }

    private

     void operator_map() {
      super_value = super.dup
      super_value['='] = ::Queries::Operators::BooleanEquals
      super_value['!'] = ::Queries::Operators::BooleanNotEquals

      super_value
    }

     void too_many_values() {
      values.reject(&:blank?).length > 1
    }
  }
}
