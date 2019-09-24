#ifndef OPENPROJ_MODELS_ENTERPRISE_TOKEN_H
#define OPENPROJ_MODELS_ENTERPRISE_TOKEN_H


#include "activerecord.h"
#include "EnterpriseTokens.h"

namespace openproj {

namespace models {

class EnterpriseToken : public openproj::models::ActiveRecord::Base, public drogon_model::openproject6::EnterpriseTokens {
  public:
    //  class << self {
    //     void current() {
    //      RequestStore.fetch(:current_ee_token) {
    //        set_current_token
    //      }
    //    }
    //     void table_exists?() {
    //      connection.data_source_exists? this->table_name
    //    }
    //     void allows_to?(action) {
    //      Authorization::EnterpriseService.new(current).call(action).result
    //    }
    //     void show_banners?() {
    //      OpenProject::Configuration.ee_manager_visible? && (!current || current.expired?)
    //    }
    inline void set_current_token() {
    //      token = EnterpriseToken.order(Arel.sql("created_at DESC")).first
    
    //      if ( token && token.token_object) {
    //        token
    //      }
    //    }
      };

    // validates_presence_of :encoded_token
    //  validate :valid_token_object
    //  before_save :unset_current_token
    //  before_destroy :unset_current_token
    // delegate :will_expire?,
    //          :expired?,
    //          :subscriber,
    //          :mail,
    //          :issued_at,
    //          :starts_at,
    //          :expires_at,
    //          :restrictions,
    //          to: :token_object
    inline void token_object() {
    //    load_token! unless defined?(this->token_object)
    //    this->token_object
      };

    //   void allows_to?(action) {
    //    Authorization::EnterpriseService.new(self).call(action).result
    //  }
    inline void unset_current_token() {
        // Clear current cache
    //    RequestStore.delete :current_ee_token
      };
private:
    //   void load_token!() {
    //    this->token_object = OpenProject::Token.import(encoded_token)
    //  rescue OpenProject::Token::ImportError => error
    //    Rails.logger.error "Failed to load EE token: #{error}"
    //    nil
    //  }
    inline void valid_token_object() {
    //    errors.add(:encoded_token, :unreadable) unless load_token!
      };

};

} // namespace openproj::models

} // namespace openproj
#endif
