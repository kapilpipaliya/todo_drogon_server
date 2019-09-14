namespace openproject {
class Authorization::QueryTransformationsOrder
   QueryTransformationsOrder() {
    this->array = []
  }

  // delegate :<<, :map, to: :array

   void full_order() {
    partial_orders = transformation_partial_orders

    merge_transformation_partial_orders(partial_orders)
  }

  private:

  // attr_accessor :array

   void transformation_partial_orders() {
    map { |transformation|
      transformation.after + [transformation.name] + transformation.before
    }
  }

   void merge_transformation_partial_orders(partial_orders) {
    desired_order = []

    until partial_orders.empty?
      order = partial_orders.shift

      shift_first_if_its_turn(order, partial_orders) { |first|
        desired_order << first
      }

      partial_orders.push(order) unless order.empty?
    }

    desired_order
  }

   void shift_first_if_its_turn(order, partial_orders) {
    this->rejected ||= []

    if ( first_not_included_or_first_everywhere(order, partial_orders)) {
      partial_orders.select { |o| o[0] == order[0] }.each(&:shift)

      this->rejected.clear
      yield order.shift
    else
      raise "Cannot sort #{order} into the list of transformations" if ( this->rejected.include?(order)) {

      this->rejected << order
    }
  }

   void first_not_included_or_first_everywhere(order, partial_orders) {
    partial_orders.all? { |o| !o.include?(order[0]) || o[0] == order[0] }
  }
}
