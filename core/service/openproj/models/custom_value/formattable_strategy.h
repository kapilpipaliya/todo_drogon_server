class
  CustomValue::FormattableStrategy < CustomValue::FormatStrategy

   void formatted_value() {
    OpenProject::TextFormatting::Renderer.format_text value
  }

   void typed_value() {
    value.to_s
  }

   void validate_type_of_value; }() {
}
