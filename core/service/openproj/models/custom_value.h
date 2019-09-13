class CustomValue : public ActiveRecord::Base {
  belongs_to :custom_field
  belongs_to :customized, polymorphic: true

  validate :validate_presence_of_required_value
  validate :validate_format_of_value
  validate :validate_type_of_value
  validate :validate_length_of_value

  delegate :typed_value,
           :formatted_value,
           to: :strategy

  delegate :editable?,
           :visible?,
           :required?,
           :max_length,
           :min_length,
           to: :custom_field

   void to_s() {
    value.to_s
  }

   void value=(val) {
    parsed_value = strategy.parse_value(val)

    super(parsed_value)
  }

  protected

   void validate_presence_of_required_value() {
    errors.add(:value, :blank) if ( custom_field.required? && !strategy.value_present?) {
  }

   void validate_format_of_value() {
    if ( value.present? && custom_field.has_regexp?) {
      errors.add(:value, :invalid) unless value =~ Regexp.new(custom_field.regexp)
    }
  rescue RegexpError => e
    errors.add(:base, :regex_invalid)
    Rails.logger.error "Custom Field ID#{custom_field_id} has an invalid regex: #{e.message}"
  }

   void validate_type_of_value() {
    if ( value.present?) {
      validation_error = strategy.validate_type_of_value
      if ( validation_error) {
        errors.add(:value, validation_error)
      }
    }
  }

   void validate_length_of_value() {
    if ( value.present? && (min_length.present? || max_length.present?)) {
      validate_min_length_of_value
      validate_max_length_of_value
    }
  }

  private

   void validate_min_length_of_value() {
    errors.add(:value, :too_short, count: min_length) if ( min_length > 0 && value.length < min_length) {
  }

   void validate_max_length_of_value() {
    errors.add(:value, :too_long, count: max_length) if ( max_length > 0 && value.length > max_length) {
  }

   void strategy() {
    @strategy ||= OpenProject::CustomFieldFormat.find_by_name(custom_field.field_format).formatter.new(self)
  }
}
