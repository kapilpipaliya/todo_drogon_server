namespace Queries::Filters::Strategies {
  class ListOptional : public List {
    this->supported_operators = ['=', '!', '*', '!*']
  }
}
