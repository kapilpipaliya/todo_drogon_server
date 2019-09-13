namespace Queries::Filters::Strategies {
  class Integer : public BaseStrategy {
    include Queries::Filters::Strategies::Numeric
    include Queries::Filters::Strategies::IntegerNumeric
  }
}
