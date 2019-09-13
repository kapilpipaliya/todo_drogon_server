namespace CustomActions::Actions::Strategies::AssociatedCustomField {
  include CustomActions::Actions::Strategies::Associated
  include CustomActions::Actions::Strategies::CustomField

   void associated() {
    custom_field
      .possible_values_options
      .map { |label, value| [value.empty? ? nil : value.to_i, label] }
  }
}
