namespace Queries::Filters::Strategies {
  class Search : public BaseStrategy {
    this->supported_operators = ['**']
    this->default_operator = '**'
  }
}
