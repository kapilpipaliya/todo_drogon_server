namespace Queries::Filters::Strategies {
  class DateInterval : public Queries::Filters::Strategies::Date {
    this->supported_operators = ['<>d']
    this->default_operator = '<>d'
  }
}
