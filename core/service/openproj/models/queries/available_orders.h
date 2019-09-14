namespace Queries::AvailableOrders {
   void order_for(key) {
    (find_registered_order(key) || Queries::NotExistingOrder).new(key)
  }

  private:

   void find_registered_order(key) {
    orders_register.detect { |s|
      s.key === key.to_sym
    }
  }

   void orders_register() {
    Queries::Register.orders[this->class]
  }
}
