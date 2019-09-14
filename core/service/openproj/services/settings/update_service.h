class Settings::UpdateService : public ::BaseServices::Update {
  // attr_accessor :user

   UpdateService(user) {
    this->user = user
  }

   void call(settings:) {
    settings.each { |name, value|
      if ( value.is_a?(Array)) {
        // remove blank values in array settings
        value.delete_if ((&:blank?)) {
      } else if ( value.is_a?(Hash)) {
        value.delete_if ( { |_, v| v.blank? }) {
      else
        value = value.strip
      }
      Setting[name] = value
    }
  }
}
