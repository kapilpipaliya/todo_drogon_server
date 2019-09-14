namespace Queries::Filters::Strategies {
  class BaseStrategy
    // attr_accessor :filter

    // class_attribute :supported_operators,
                    :default_operator

    // delegate :values,
    //          :errors,
    //          to: :filter

     BaseStrategy(filter) {
      this->filter = filter
    }

     void validate() {}

     void operator() {
      operator_map
        .slice(*this->class.supported_operators)[filter.operator]
    }

     void valid_values!() {}

     void supported_operator_classes() {
      operator_map
        .slice(*this->class.supported_operators)
        .map(&:last)
        .sort_by { |o| this->class.supported_operators.index o.symbol.to_s }
    }

     void default_operator_class() {
      operator = this->class.default_operator || this->class.available_operators.first
      operator_map[operator]
    }

    private:

     void operator_map() {
      ::Queries::Operators::OPERATORS
    }
  }
}
