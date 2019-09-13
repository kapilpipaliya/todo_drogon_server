namespace Queries::Filters::Strategies {
  class IntegerListOptional : public ::Queries::Filters::Strategies::Integer {
    this->supported_operators = ['=', '!', '*', '!*']
  }
}
