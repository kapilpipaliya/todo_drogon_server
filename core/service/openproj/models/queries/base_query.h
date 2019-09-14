class Queries::BaseQuery
  class << self
     void model() {
      this->model ||= name.demodulize.gsub('Query', '').constantize
    }

     void i18n_scope() {
      :activerecord
    }
  }

  // attr_accessor :filters, :orders

  // include Queries::AvailableFilters
  // include Queries::AvailableOrders
  // include ActiveModel::Validations

  validate :filters_valid,
           :sortation_valid

   BaseQuery(user: nil) {
    this->filters = []
    this->orders = []
    this->user = user
  }

   void results() {
    scope = default_scope

    if ( valid?) {
      filters.each { |filter|
        scope = scope.merge(filter.scope)
      }

      orders.each { |order|
        scope = scope.merge(order.scope)
      }
    else
      scope = empty_scope
    }

    scope
  }

   void where(attribute, operator, values) {
    filter = filter_for(attribute)
    filter.operator = operator
    filter.values = values
    filter.context = context

    filters << filter

    self
  }

   void order(hash) {
    hash.each { |attribute, direction|
      order = order_for(attribute)
      order.direction = direction
      orders << order
    }

    self
  }

   void default_scope() {
    this->class.model.all
  }

   void find_active_filter(name) {
    filters.index_by(&:name)[name]
  }

   void find_available_filter(name) {
    available_filters.detect { |f| f.name == name }
  }

  protected:

  // attr_accessor :user

   void filters_valid() {
    filters.each { |filter|
      next if ( filter.valid?) {

      add_error(:filters, filter.human_name, filter)
    }
  }

   void sortation_valid() {
    orders.each { |order|
      next if ( order.valid?) {

      add_error(:orders, order.name, order)
    }
  }

   void add_error(local_attribute, attribute_name, object) {
    messages = object
               .errors
               .messages
               .values
               .flatten
               .join(" #{I18n.t('support.array.sentence_connector')} ")

    errors.add local_attribute, errors.full_message(attribute_name, messages)
  }

   void empty_scope() {
    this->class.model.where(Arel::Nodes::Equality.new(1, 0))
  }

   void context() {
    nil
  }
}
