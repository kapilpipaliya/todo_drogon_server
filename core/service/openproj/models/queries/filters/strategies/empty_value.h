namespace Queries::Filters::Strategies {
  class EmptyValue : public BaseStrategy {
     void validate() {
      super

      unless values.empty?
        errors.add(:values, "must be empty")
      }
    }
  }
}
