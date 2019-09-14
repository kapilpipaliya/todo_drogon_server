
class Queries::WorkPackages::Filter::FilterConfiguration
  // attr_accessor(:filter_class, :filter_name, :operator)

   FilterConfiguration(filter_class, filter_name, operator) {
    this->filter_class = filter_class
    this->filter_name = filter_name
    this->operator = operator
  }
}
