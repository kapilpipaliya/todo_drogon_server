#pragma once
#include <drogon/drogon.h>
#include <vector>
#include "models/UserPasswords.h"
#include "models/Users.h"
#include "seeder.h"

#include "../models/user.h"

namespace openproj {
namespace seeder {
class AdminUserSeeder : public Seeder {
 public:
  void seed_data() {
    //    user = new_admin()
    //    unless user.save! validate: false
    //      puts "Seeding admin failed:"
    //      user.errors.full_messages.each { |msg|
    //        puts "  #{msg}"
    //      }
    //    }
    auto clientPtr = drogon::app().getDbClient("sce");

    drogon::orm::Mapper<drogon_model::openproject6::Users> mapper_users(
        clientPtr);

    auto result_users = mapper_users.findBy(
        (Criteria(drogon_model::openproject6::Users::Cols::_type,
                  CompareOperator::EQ, "SystemUser")));
    if (result_users.size() > 0) {
      LOG_DEBUG << "not creating system user";
    } else {
      drogon_model::openproject6::Users system_user;
      system_user.setAdmin(false);
      system_user.setLogin("");
      system_user.setFirstname("");
      system_user.setLastname("System");
      system_user.setMail("");

      system_user.setLanguage("en");
      system_user.setMailNotification("only_my_events");
      system_user.setType("SystemUser");
      system_user.setStatus(
          openproj::models::Principal::STATUSES::locked);  // this is default
      system_user.setForcePasswordChange(false);
      system_user.setFirstLogin(false);  // this is default
      system_user.setCreatedOn(trantor::Date::now());
      system_user.setUpdatedOn(trantor::Date::now());
      mapper_users.insert(system_user);
    }

    drogon_model::openproject6::Users admin_user;
    admin_user.setAdmin(true);
    admin_user.setLogin("admin");
    //     user.set
    admin_user.setFirstname("OpenProject");
    admin_user.setLastname("Admin");
    admin_user.setMail("admin@example.net");
    admin_user.setLanguage("en");
    admin_user.setMailNotification("only_my_events");
    admin_user.setType("User");
    admin_user.setStatus(
        openproj::models::Principal::STATUSES::active);  // this is default
    admin_user.setForcePasswordChange(false);
    admin_user.setFirstLogin(true);  // this is default
    admin_user.setCreatedOn(trantor::Date::now());
    admin_user.setUpdatedOn(trantor::Date::now());
    mapper_users.insert(admin_user);

    // Look at database
    /*
    drogon_model::openproject6::Users anonymous_user;
    anonymous_user.setAdmin(false);
    anonymous_user.setLogin("");
    anonymous_user.setFirstname("");
    anonymous_user.setLastname("System");
    anonymous_user.setMail("");

    anonymous_user.setLanguage("en");
    anonymous_user.setMailNotification("only_my_events");
    anonymous_user.setType("SystemUser");
    anonymous_user.setStatus(
        openproj::models::Principal::STATUSES::locked);  // this is default
    anonymous_user.setForcePasswordChange(false);
    anonymous_user.setFirstLogin(false);  // this is default
    anonymous_user.setCreatedOn(trantor::Date::now());
    anonymous_user.setUpdatedOn(trantor::Date::now());
    mapper_users.insert(anonymous_user);
*/

    drogon::orm::Mapper<drogon_model::openproject6::UserPasswords>
        mapper_user_passwords(clientPtr);
    drogon_model::openproject6::UserPasswords user_passwords;
    // UserPassword::Bcrypt Create (0.9ms)  INSERT INTO "user_passwords"
    // ("user_id", "hashed_password", "created_at", "updated_at", "type") VALUES
    // ($1, $2, $3, $4, $5) RETURNING "id"  [["user_id", 2], ["hashed_password",
    // "$2a$12$FDuVT81rIi8Ip4lEAhCyqe8GS1RbRDEfK2L9zzn36belEgoyt7yyK"],
    // ["created_at", "2019-09-19 20:55:47.415914"], ["updated_at", "2019-09-19
    // 20:55:47.415914"], ["type", "UserPassword::Bcrypt"]] D,
    // [2019-09-20T02:25:47.675273 #19304] DEBUG -- :   ↳
    // app/models/user.rb:163:in `update_password"
    user_passwords.setUserId(*admin_user.getId());  // integer NOT_NULL ;
    user_passwords.setHashedPassword(
        "admin");                     // character_varying(128) NOT_NULL ;
    user_passwords.setSalt("12345");  // character_varying(64)  ;
    user_passwords.setCreatedAt(
        trantor::Date::now());  // timestamp_without_time_zone  ;
    user_passwords.setUpdatedAt(
        trantor::Date::now());         // timestamp_without_time_zone  ;
    user_passwords.setType("Bcrypt");  // character_varying NOT_NULL ;

    mapper_user_passwords.insert(user_passwords);
  }

  bool applicable() {
    //    User.admin.empty?
  }

  void not_applicable_message() {
    //    "No need to seed an admin as there already is one."
  }

  void new_admin() {
    //    User.new.tap { |user|
    //      user.admin = true
    //      user.login = "admin"
    //      user.password = "admin"
    //      user.firstname = "OpenProject"
    //      user.lastname = "Admin"
    //      user.mail = ENV.fetch("ADMIN_EMAIL") { "admin@example.net" }
    //      user.mail_notification =
    //      UserN::USER_MAIL_OPTION_ONLY_MY_EVENTS.first user.language =
    //      I18n.locale.to_s user.status = UserN::STATUSES[:active]
    //      user.force_password_change = force_password_change?
    //    }
  }

  bool force_password_change() {
    //    Rails.env != "development" && !force_password_change_disabled?
  }

  bool force_password_change_disabled() {
    //    off_values = ["off", "false", "no", "0"]

    //    off_values.include? ENV[force_password_change_env_switch_name]
  }

  void force_password_change_env_switch_name() {
    //    "OP_ADMIN_USER_SEEDER_FORCE_PASSWORD_CHANGE"
  }
};
}  // namespace seeder
}  // namespace openproj
