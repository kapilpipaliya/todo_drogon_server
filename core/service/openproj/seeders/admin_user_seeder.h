#pragma once
#include "seeder.h"
namespace openproj {
namespace seeder {
class AdminUserSeeder : public Seeder {
public:
   void seed_data() {
//    user = new_admin
//    unless user.save! validate: false
//      puts 'Seeding admin failed:'
//      user.errors.full_messages.each { |msg|
//        puts "  #{msg}"
//      }
//    }
  }

   bool applicable() {
//    User.admin.empty?
  }

   void not_applicable_message() {
//    'No need to seed an admin as there already is one.'
  }

   void new_admin() {
//    User.new.tap { |user|
//      user.admin = true
//      user.login = 'admin'
//      user.password = 'admin'
//      user.firstname = 'OpenProject'
//      user.lastname = 'Admin'
//      user.mail = ENV.fetch('ADMIN_EMAIL') { 'admin@example.net' }
//      user.mail_notification = UserN::USER_MAIL_OPTION_ONLY_MY_EVENTS.first
//      user.language = I18n.locale.to_s
//      user.status = UserN::STATUSES[:active]
//      user.force_password_change = force_password_change?
//    }
  }

   bool force_password_change() {
//    Rails.env != 'development' && !force_password_change_disabled?
  }

   bool force_password_change_disabled() {
//    off_values = ["off", "false", "no", "0"]

//    off_values.include? ENV[force_password_change_env_switch_name]
  }

   void force_password_change_env_switch_name() {
//    "OP_ADMIN_USER_SEEDER_FORCE_PASSWORD_CHANGE"
  }
};
}
}
