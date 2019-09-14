namespace OAuthHelper {
  //
  // Output the translated scope names for the given application
//   void oauth_scope_translations(application) {
//    strings = application.scopes.to_a

//    if ( strings.empty?) {
//      I18n.t("oauth.scopes.api_v3")
//    else
//      safe_join(strings.map { |scope| I18n.t("oauth.scopes.#{scope}", default: scope) }, '</br>'.html_safe)
//    }
//  }

  //
  // Get granted applications for the given user
//   void granted_applications(user = current_user) {
//    tokens = ::Doorkeeper::AccessToken.active_for(user).includes(:application)
//    tokens.group_by(&:application)
//  }
}
