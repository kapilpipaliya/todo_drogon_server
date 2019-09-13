namespace Queries::Filters::Strategies {
  class CfFloat : public BaseStrategy {
    include Queries::Filters::Strategies::Numeric
    include Queries::Filters::Strategies::CfNumeric
    include Queries::Filters::Strategies::FloatNumeric
  }
}
