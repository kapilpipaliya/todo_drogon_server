#pragma once
//#include "uri"
//#include "cgi"

// This capsulates the validation of a requested redirect URL.
//
namespace openproj {
class RedirectPolicy{
//  attr_reader :validated_redirect_url, :request

//   RedirectPolicy(requested_url, hostname:, default:, return_escaped: true) {
//    this->current_host = hostname
//    this->return_escaped = return_escaped

//    this->requested_url = preprocess(requested_url)
//    this->default_url = default
//  }

  //
  // Performs all validations for the requested URL
   bool valid() {
//    if ( this->requested_url.nil?) { return false ;}

//    [
//      // back_url must not contain two consecutive dots
//      :no_upper_levels,
//      // Require the path to begin with a slash
//      :path_has_slash,
//      // do not redirect user to another host
//      :same_host,
//      // do not redirect user to the login or register page
//      :path_not_blacklisted,
//      // do not redirect to another subdirectory
//      :matches_relative_root
//    ].all? { |check| send(check) }
  }

  //
  // Return a valid redirect URI.
  // If the validation check on the current back URL apply
   void redirect_url() {
//    if ( valid?) {
//      postprocess(this->requested_url)
//    else
//      this->default_url
//    }
  }

  private:

  //
  // Preprocesses the requested redirect URL.
  // - Escapes it when necessary
  // - Tries to parse it
  // - Escapes the redirect URL when requested so.
//   void preprocess(requested) {
//    url = URI.escape(CGI.unescape(requested.to_s))
//    URI.parse(url)
//  rescue URI::InvalidURIError => e
//    Rails.logger.warn("Encountered invalid redirect URL '#{requested}': #{e.message}")
//    nil
//  }

  //
  // Postprocesses the validated URL
//   void postprocess(redirect_url) {
//    // Remove basic auth credentials
//    redirect_url.userinfo = ''

//    if ( this->return_escaped) {
//      redirect_url.to_s
//    else
//      URI.unescape(redirect_url.to_s)
//    }
//  }

  //
  // Avoid paths with references to parent paths
   void no_upper_levels() {
//    !this->requested_url.path.include? '../'
  }

  //
  // Require URLs to contain a path slash.
  // This will always be the case for parsed URLs unless
  // +URI.parse('this->foo.bar')+ or a non-root relative URL  +URI.parse('foo')+
   void path_has_slash() {
//    this->requested_url.path =~ %r{\A/([^/]|\z)}
  }

  //
  // do not redirect user to another host (even protocol relative urls have the host set)
  // whenever a host is set it must match the request's host
   void same_host() {
//    this->requested_url.host.nil? || this->requested_url.host == this->current_host
  }

  //
  // Avoid redirect URLs to specific locations, such as login page
   void path_not_blacklisted() {
//    !this->requested_url.path.match(
//      %r{/(
//      // Ignore login since redirect to back url is result of successful login.
//      login |
//      // When signing out with a direct login provider enabled you will be left at the logout
//      // page with a message indicating that you were logged out. Logging in from there would
//      // normally cause you to be redirected to this page. As it is the logout page, however,
//      // this would log you right out again after a successful login.
//      logout |
//      // Avoid sending users to the register form. The exact reasoning behind
//      // this is unclear, but grown from tradition.
//      account/register
//      )}x // ignore whitespace
//    )
  }

  //
  // Requires the redirect URL to reside inside the relative root, when given.
   void matches_relative_root() {
//    relative_root = OpenProject::Configuration['rails_relative_url_root']
//    relative_root.blank? || this->requested_url.path.starts_with?(relative_root)
  }
};
}
