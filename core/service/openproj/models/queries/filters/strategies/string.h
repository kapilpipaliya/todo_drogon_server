namespace Queries::Filters::Strategies {
  class String : public BaseStrategy {
    this->supported_operators = ['=', '~', '!', '!~']
    this->default_operator = '~'
  }
}
