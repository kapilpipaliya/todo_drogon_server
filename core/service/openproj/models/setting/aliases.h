namespace openproject {
class Setting

  //
  // Shorthand to common setting aliases to avoid checking values
  namespace Aliases {

    //
    // Whether the application is configured to use or force SSL output
    // for cookie storage et al.
     void https?() {
      Setting.protocol == 'https' || Rails.configuration.force_ssl
    }
  }
}
