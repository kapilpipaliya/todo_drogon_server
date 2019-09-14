class Queries::Projects::Orders::CustomFieldOrder : public Queries::BaseOrder {
  this->model = Project.all

  // validates :custom_field, presence: { message: I18n.t(:'activerecord.errors.messages.does_not_exist') }

   void key() {
    /cf_(\d+)/
  }

   void custom_field() {
    @custom_field ||= begin
      id = this->class.key.match(attribute)[1]

      ProjectCustomField.visible.find_by_id(id)
    }
  }

   void scope() {
    super.select(custom_field.order_statements)
  }

  private:

   void order() {
    joined_statement = custom_field.order_statements.map { |statement|
      "#{statement} #{direction}"
    }.join(', ')

    model.order(joined_statement)
  }
}
