namespace Queries::Filters::Strategies {
  class IntegerList : public ::Queries::Filters::Strategies::Integer {
    this->supported_operators = ['!', '=']
  }
}
