namespace Queries::Filters::Strategies {
  class Text : public BaseStrategy {
    this->supported_operators = ['~', '!~']
    this->default_operator = '~'
  }
}