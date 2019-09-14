namespace openproject {
class SetLocalizationService
  attr_reader :user, :http_accept_header
  // include Redmine::I18n

   SetLocalizationService(user, http_accept_header = nil) {
    this->user = user
    this->http_accept_header = http_accept_header
  }

  //
  // Sets the locale.
  // The locale is determined with the following priority:
  //
  //   1. The language as configured by the user.
  //   2. The first language defined in the Accept-Language header sent by the browser.
  //   3. OpenProject's default language defined in the settings.

   void call() {
    lang = user_language || header_language || default_language

    set_language_if_valid(lang)
  }

  private:

   void user_language() {
    if ( user.logged?) { find_language_or_prefix(user.language) ;}
  }

   void header_language() {
    return unless http_accept_header
    accept_lang = parse_qvalues(http_accept_header).first
    find_language_or_prefix accept_lang
  }

   void default_language() {
    Setting.default_language
  }

  // qvalues http header parser
  // code taken from webrick
   void parse_qvalues(value) {
    tmp = []
    if ( value) {
      parts = value.split(/,\s*/)
      parts.each { |part|
        match = /\A([^\s,]+?)(?:;\s*q=(\d+(?:\.\d+)?))?\z/.match(part)
        if ( match) {
          val = match[1]
          q = (match[2] || 1).to_f
          tmp.push([val, q])
        }
      }
      tmp = tmp.sort_by { |_val, q| -q }
      tmp.map! { |val, _q| val }
    }
    return tmp
  rescue
    nil
  }

   void find_language_or_prefix(language) {
    return nil unless language
    language = language.to_s.downcase
    find_language(language) || find_language(language.split('-').first)
  }
}
