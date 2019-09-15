#pragma once
//#include "uri"

//
// Intended to be used by the AccountController to handle omniauth logins
namespace openproj {
namespace Concerns::OmniauthLogin {
  // extend ActiveSupport::Concern

//  included {
//    // disable CSRF protection since that should be covered by the omniauth strategy
//    // the other filters are not applicable either since OmniAuth is doing authentication
//    // itself
//    [
//      :verify_authenticity_token, :user_setup,
//      :check_if_login_required, :check_session_lifetime
//    ]
//      .each { |key| // skip_before_action key, only: [:omniauth_login] }

//    helper :omniauth
//  }

   void omniauth_login() {
//    auth_hash = request.env['omniauth.auth']

//    return render_400 unless auth_hash.valid?

//    // Set back url to page the omniauth login link was clicked on
//    params[:back_url] = request.env['omniauth.origin']

//    user_attributes = omniauth_hash_to_user_attributes(auth_hash)
//    user =
//      if ( session.include? :invitation_token) {
//        tok = Token::Invitation.find_by value: session[:invitation_token]
//        u = tok.user
//        u.identity_url = user_attributes[:identity_url]
//        tok.destroy
//        session.delete :invitation_token
//        u
//      else
//        find_or_initialize_user_with(user_attributes)
//      }

//    decision = OpenProject::OmniAuth::Authorization.authorized? auth_hash
//    if ( decision.approve?) {
//      authorization_successful user, auth_hash
//    else
//      authorization_failed user, decision.message
//    }
  }

//   void find_or_initialize_user_with(user_attributes = {}) {
//    user = User.find_by(identity_url: user_attributes[:identity_url])
//    return user unless user.nil?

//    if ( Setting.oauth_allow_remapping_of_existing_users?) {
//      // Allow to map existing users with an Omniauth source if ( the login) {
//      // already exists, and no existing auth source or omniauth provider is
//      // linked
//      user = User.find_by(
//        login: user_attributes[:login],
//        identity_url: nil,
//        auth_source_id: nil
//      )
//    }

//    if ( user.nil?) {
//      User.new(identity_url: user_attributes[:identity_url])
//    else
//      // We might want to update all the attributes from the provider, but for
//      // backwards-compatibility only the identity_url is updated here
//      user.update_attribute :identity_url, user_attributes[:identity_url]
//      user
//    }
//  }

   void omniauth_failure() {
//    if ( params[:message]) { logger.warn(params[:message]) ;}
//    show_error I18n.t(:error_external_authentication_failed)
  }

//   void direct_login_provider_url(params = {}) {
//    omniauth_start_url(direct_login_provider, params)
//  }

//  private:

//   void authorization_successful(user, auth_hash) {
//    if ( user.new_record? || user.invited?) {
//      create_user_from_omniauth user, auth_hash
//    else
//      if ( user.active?) {
//        user.log_successful_login
//        OpenProject::OmniAuth::Authorization.after_login! user, auth_hash, self
//      }
//      login_user_if_active(user)
//    }
//  }

//   void authorization_failed(user, error) {
//    logger.warn "Authorization for User #{user.id} failed: #{error}"
//    show_error error
//  }

//   void show_error(error) {
//    flash[:error] = error
//    redirect_to action: 'login'
//  }

  // a user may login via omniauth and (if ( that user does not exist) {
  // in our database) will be created using this method.
//   void create_user_from_omniauth(user, auth_hash) {
//    // Self-registration off
//    return self_registration_disabled unless Setting.self_registration? || user.invited?

//    fill_user_fields_from_omniauth user, auth_hash

//    opts = {
//      omni_auth_hash: auth_hash
//    }

//    // only enforce here so user has email filled in for the admin notification
//    // about who couldn't register/activate
//    if ( enforce_activation_user_limit(user: user)) { return ;}

//    // Create on the fly
//    register_user_according_to_setting(user, opts) {
//      // Allow registration form to show provider-specific title
//      this->omniauth_strategy = auth_hash[:provider]

//      // Store a timestamp so we can later make sure that authentication information can
//      // only be reused for a short time.
//      session_info = auth_hash.merge(omniauth: true, timestamp: Time.new)

//      onthefly_creation_failed(user, session_info)
//    }
//  }

//   void register_via_omniauth(user, session, permitted_params) {
//    auth = session[:auth_source_registration]
//    if ( handle_omniauth_registration_expired(auth)) { return ;}

//    fill_user_fields_from_omniauth(user, auth)
//    user.update_attributes(permitted_params.user_register_via_omniauth)

//    opts = {
//      omni_auth_hash: auth
//    }
//    register_user_according_to_setting user, opts
//  }

//   void fill_user_fields_from_omniauth(user, auth) {
//    user.assign_attributes omniauth_hash_to_user_attributes(auth)
//    user.register unless user.invited?
//    user
//  }

//   void omniauth_hash_to_user_attributes(auth) {
//    info = auth[:info]

//    attribute_map = {
//      login:        info[:email],
//      mail:         info[:email],
//      firstname:    info[:first_name] || info[:name],
//      lastname:     info[:last_name],
//      identity_url: identity_url_from_omniauth(auth)
//    }

//    // Allow strategies to override mapping
//    strategy = request.env['omniauth.strategy']
//    if ( strategy.respond_to?(:omniauth_hash_to_user_attributes)) {
//      attribute_map.merge(strategy.omniauth_hash_to_user_attributes(auth))
//    else
//      attribute_map
//    }
//  }

//   void identity_url_from_omniauth(auth) {
//    "#{auth[:provider]}:#{auth[:uid]}"
//  }

  // if the omni auth registration happened too long ago,
  // we don't accept it anymore.
//   void handle_omniauth_registration_expired(auth) {
//    if ( auth['timestamp'] < Time.now - 30.minutes) {
//      flash[:error] = I18n.t(:error_omniauth_registration_timed_out)
//      redirect_to(signin_url)
//    }
//  }

//   void url_with_params(url, params = {}) {
//    URI.parse(url).tap { |uri|
//      query = URI.decode_www_form(uri.query || '')
//      params.each { |key, value|
//        query << [key, value]
//      }
//      uri.query = URI.encode_www_form(query) unless query.empty?
//    }.to_s
//  }
}
}
