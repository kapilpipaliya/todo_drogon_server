#pragma once
//#include "net/ldap"
#include "auth_source.h"

namespace openproj {
namespace models {
class LdapAuthSource : public AuthSource {
//  enum tls_mode: %w[plain_ldap simple_tls start_tls]
  // validates :tls_mode, inclusion: { in: tls_modes.keys }

  // validates_presence_of :host, :port, :attr_login
  // validates_length_of :name, :host, maximum: 60, allow_nil: true
  // validates_length_of :account, :account_password, :base_dn, maximum: 255, allow_nil: true
  // validates_length_of :attr_login, :attr_firstname, :attr_lastname, :attr_mail, :attr_admin, maximum: 30, allow_nil: true
  // validates_numericality_of :port, only_integer: true

//  before_validation :strip_ldap_attributes
//  after_initialize :set_default_port

//   void authenticate(login, password) {
//    if ( login.blank? || password.blank?) { return nil ;}
//    attrs = get_user_dn(login)

//    if ( attrs && attrs[:dn] && authenticate_dn(attrs[:dn], password)) {
//      Rails.logger.debug { "Authentication successful for "#{login}"" }
//      return attrs.except(:dn)
//    }
//  rescue  Net::LDAP::LdapError => error
//    raise "LdapError: " + error.message
//  }

//   void find_user(login) {
//    if ( login.blank?) { return nil ;}
//    attrs = get_user_dn(login)

//    if ( attrs && attrs[:dn]) {
//      Rails.logger.debug { "Lookup successful for "#{login}"" }
//      return attrs.except(:dn)
//    }
//  rescue  Net::LDAP::LdapError => error
//    raise "LdapError: " + error.message
//  }

//  // test the connection to the LDAP
//   void test_connection() {
//    unless authenticate_dn(account, account_password)
//      raise I18n.t("auth_source.ldap_error", error_message: I18n.t("auth_source.ldap_auth_failed"))
//    }
//  rescue  Net::LDAP::LdapError => text
//    raise I18n.t("auth_source.ldap_error", error_message: text.to_s)
//  }

//   void auth_method_name() {
//    "LDAP"
//  }

  private:

//   void strip_ldap_attributes() {
//    [:attr_login, :attr_firstname, :attr_lastname, :attr_mail, :attr_admin].each { |attr|
//      write_attribute(attr, read_attribute(attr).strip) unless read_attribute(attr).nil?
//    }
//  }

//   void initialize_ldap_con(ldap_user, ldap_password) {
//    options = { host: host,
//                port: port,
//                force_no_page: true,
//                encryption: ldap_encryption
//              }
//    options.merge!(auth: { method: :simple, username: ldap_user, password: ldap_password }) unless ldap_user.blank? && ldap_password.blank?
//    Net::LDAP.new options
//  }

//   void ldap_encryption() {
//    if ( tls_mode == "plain_ldap") {
//      nil
//    else
//      tls_mode.to_sym
//    }
//  }

//   void get_user_attributes_from_ldap_entry(entry) {
//    {
//      dn: entry.dn,
//      firstname: LdapAuthSource.get_attr(entry, attr_firstname),
//      lastname: LdapAuthSource.get_attr(entry, attr_lastname),
//      mail: LdapAuthSource.get_attr(entry, attr_mail),
//      admin: !!LdapAuthSource.get_attr(entry, attr_admin),
//      auth_source_id: id
//    }
//  }

//  // Return the attributes needed for the LDAP search.  It will only
//  // include the user attributes if ( on-the-fly registration is enabled) {
//   void search_attributes() {
//    if ( onthefly_register?) {
//      ["dn", attr_firstname, attr_lastname, attr_mail, attr_admin]
//    else
//      ["dn"]
//    }
//  }

//  // Check if ( a DN (user record) authenticates with the password) {
//   void authenticate_dn(dn, password) {
//    if ( dn.present? && password.present?) {
//      initialize_ldap_con(dn, password).bind
//    }
//  }

//  // Get the user"s dn and any attributes for them, given their login
//   void get_user_dn(login) {
//    ldap_con = initialize_ldap_con(account, account_password)
//    login_filter = Net::LDAP::Filter.eq(attr_login, login)
//    object_filter = Net::LDAP::Filter.eq("objectClass", "*")
//    attrs = {}

//    Rails.logger.debug {
//      "LDAP initializing search (BASE=#{base_dn}), (FILTER=#{(object_filter & login_filter).to_s})"
//    }
//    ldap_con.search(base: base_dn,
//                    filter: object_filter & login_filter,
//                    attributes: search_attributes) { |entry|
//      if ( onthefly_register?) {
//        attrs = get_user_attributes_from_ldap_entry(entry)
//      else
//        attrs = { dn: entry.dn }
//      }

//      Rails.logger.debug { "DN found for #{login}: #{attrs[:dn]}" }
//    }

//    attrs
//  }

//   void get_attr(entry, attr_name) {
//    if ( !attr_name.blank?) {
//      entry[attr_name].is_a?(Array) ? entry[attr_name].first : entry[attr_name]
//    }
//  }

//   void set_default_port() {
//    if ( port.to_i == 0) { this->port = 389 ;}
//  }
};
}

}