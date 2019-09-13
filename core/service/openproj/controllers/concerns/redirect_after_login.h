//
// Intended to be used by the AccountController to decide where to
// send the user when they logged in.
namespace Concerns::RedirectAfterLogin {
   void redirect_after_login(user) {
    if ( user.first_login) {
      user.update_attribute(:first_login, false)
      first_login_redirect
    else
      default_redirect
    }
  }

  //    * * *

   void default_redirect() {
    if ( url = OpenProject::Configuration.after_login_default_redirect_url) {
      redirect_to url
    else
      redirect_back_or_default my_page_path
    }
  }

   void first_login_redirect() {
    if ( url = OpenProject::Configuration.after_first_login_redirect_url) {
      redirect_to url
    else
      redirect_to home_url(first_time_user: true)
    }
  }
}
