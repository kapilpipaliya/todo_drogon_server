namespace Queries::Filters::Strategies {
  class ListAll : public List {
    this->supported_operators = ['=', '!', '*']
  }
}
