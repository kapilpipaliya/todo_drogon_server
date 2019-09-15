namespace openproj {
namespace HomescreenHelper {
  //
  // Homescreen name
   void organization_name() {
//    Setting.app_title || Setting.software_name
  }

  //
  // Homescreen organization icon
   void organization_icon() {
//    op_icon('icon-context icon-enterprise')
  }

  //
  // Returns the user avatar or a default image
   void homescreen_user_avatar() {
//    op_icon('icon-context icon-user')
  }

  //
  // Render a static link defined in OpenProject::Static::Links
//   void static_link_to(key) {
//    link = OpenProject::Static::Links.links[key]
//    label = I18n.t(link[:label])

//    link_to label,
//            link[:href],
//            title: label,
//            target: '_blank'
//  }

  //
  // Determine whether we should render the links on homescreen?
   bool show_homescreen_links() {
//    EnterpriseToken.show_banners? || OpenProject::Configuration.show_community_links?
  }

  //
  // Determine whether we should render the onboarding modal
   bool show_onboarding_modal() {
//    return OpenProject::Configuration.onboarding_enabled? && params[:first_time_user]
  }
}
}
