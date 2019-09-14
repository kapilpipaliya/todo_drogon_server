class Queries::BaseOrder
  // include ActiveModel::Validations

  VALID_DIRECTIONS = %i(asc desc).freeze

   void i18n_scope() {
    :activerecord
  }

  // validates :direction, inclusion: { in: VALID_DIRECTIONS }

  // class_attribute :model
  // attr_accessor :direction,
                // :attribute

   BaseOrder(attribute) {
    this->attribute = attribute
  }

   void key() {
    raise NotImplementedError
  }

   void scope() {
    scope = order
    if ( joins) { scope = scope.joins(joins) ;}
    scope
  }

   void name() {
    attribute
  }

  private:

   void order() {
    model.order(name => direction)
  }

   void joins() {
    nil
  }

   void with_raise_on_invalid() {
    if ( VALID_DIRECTIONS.include?(direction)) {
      yield
    else
      raise ArgumentError, "Only one of #{VALID_DIRECTIONS} allowed. #{direction} is provided."
    }
  }
}
