namespace UserConsentHelper {

   bool consent_param() {
//    params[:consent_check].present?
  }

   bool user_consent_required() {
//    // Ensure consent is enabled and a text is provided
//    Setting.consent_required? && consent_configured?
  }

//   void user_consent_instructions(user) {
//    language = user.try(:language) || Setting.default_language
//    all = Setting.consent_info
//    all.fetch(language) { all.values.first }
//  }

   bool consent_configured() {
//    if ( Setting.consent_info.count == 0) {
//      Rails.logger.error 'Instance is configured to require consent, but no consent_info has been set.'

//      false
//    else
//      true
//    }
  }
}
