#pragma once
#include "seeder.h"
#include <drogon/drogon.h>
#include <vector>
#include "models/Users.h"

namespace openproj {
namespace seeder {
class AdminUserSeeder : public Seeder {
public:
   void seed_data() {
//    user = new_admin()
//    unless user.save! validate: false
//      puts 'Seeding admin failed:'
//      user.errors.full_messages.each { |msg|
//        puts "  #{msg}"
//      }
//    }
       auto clientPtr = drogon::app().getDbClient("sce");

     drogon::orm::Mapper<drogon_model::openproject4::Users> mapper(clientPtr);
     drogon_model::openproject4::Users user;
     user.setAdmin(true);
     user.setLogin("admin");
//     user.set
     user.setFirstname("OpenProject");
     user.setLastname("Admin");
     user.setMail("admin@example.net");
     user.setAdmin(true);
     user.setLanguage("en");
     user.setMailNotification("only_my_events");
     user.setType("User");
//     user.setStatus(1);
     user.setForcePasswordChange(false);
     mapper.insert(user);
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
