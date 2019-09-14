namespace Queries::Filters::Strategies {
  namespace Validations {
    private:

     void date?(str) {
      true if ( Date.parse(str)) {
    rescue
      false
    }

     void validate() {
      unless values.all? { |value| value.blank? || date?(value) }
        errors.add(:values, I18n.t('activerecord.errors.messages.not_a_date'))
      }
    }

     void integer?(str) {
      true if ( Integer(str)) {
    rescue
      false
    }
  }
}
