#pragma once
#include "./standard_seeder/basic_data_seeder.h"
#include "admin_user_seeder.h"
#include "demo_data_seeder.h"
#include "development_data_seeder.h"
#include "drogon/drogon.h"
#include "seeder.h"

// Seeds the minimum data required to run OpenProject (BasicDataSeeder,
// AdminUserSeeder) as well as optional demo data (DemoDataSeeder) to give a
// user some orientation.
namespace openproj {
namespace seeder {
class RootSeeder : public Seeder {
 public:
  // include Redmine::I18n
  RootSeeder() {}
  void seed_data() {
    //    reset_active_record();
    set_locale();
    prepare_seed();

    do_seed();
  }

  void do_seed() {
    // ActiveRecord::Base.transaction {
    // Basic data needs be seeded before anything else.
    LOG_DEBUG << "*** Seeding basic data for "
                 "#{OpenProject::Configuration['edition']} "
                 "edition";
    openproj::seeder::StandardSeeder::BasicDataSeederFinal n;
    n.seed();

    LOG_DEBUG << "*** Seeding admin user";
    openproj::seeder::AdminUserSeeder a;
    //UserPassword::Bcrypt Create (0.9ms)  INSERT INTO "user_passwords" ("user_id", "hashed_password", "created_at", "updated_at", "type") VALUES ($1, $2, $3, $4, $5) RETURNING "id"  [["user_id", 2], ["hashed_password", "$2a$12$FDuVT81rIi8Ip4lEAhCyqe8GS1RbRDEfK2L9zzn36belEgoyt7yyK"], ["created_at", "2019-09-19 20:55:47.415914"], ["updated_at", "2019-09-19 20:55:47.415914"], ["type", "UserPassword::Bcrypt"]]
    //D, [2019-09-20T02:25:47.675273 #19304] DEBUG -- :   ↳ app/models/user.rb:163:in `update_password'
    a.seed();

    LOG_DEBUG << "*** Seeding demo data";
    openproj::seeder::DemoDataSeeder d;
    d.seed();

    //      if ( Rails.env.development?) {
    seed_development_data();
    //      }

    //      rails_engines.each { |engine|
    LOG_DEBUG << "*** Loading #{engine.engine_name} seed data";
    //        engine.load_seed
    //      }
    //    }
  }
  //   void rails_engines() {
  //    ::Rails::Engine.subclasses.map(&:instance)
  //  }
  void set_locale() {
    //    // willfully ignoring Redmine::I18n and it's
    //    // #set_language_if_valid here as it
    //    // would mean to circumvent the default settings
    //    // for valid_languages.
    //    desired_lang = (ENV['LOCALE'] || :en).to_sym

    //    if ( all_languages.include?(desired_lang)) {
    //      I18n.locale = desired_lang
    //      SPDLOG_TRACE("*** Seeding for locale: '#{I18n.locale}'"
    //    else
    //      raise "Locale #{desired_lang} is not supported"
    //    }
  }
  void prepare_seed() {
    //    // Disable mail delivery for the duration of this task
    //    ActionMailer::Base.perform_deliveries = false

    //    // Avoid asynchronous DeliverWorkPackageCreatedJob
    //    Delayed::Worker.delay_jobs = false
  }

 private:
  void seed_development_data() {
    LOG_DEBUG << "*** Seeding development data";
    //    #include "factory_bot"
    //    // Load FactoryBot factories
    //    begin
    //      ::FactoryBot.find_definitions
    //    rescue => e
    //      raise e unless e.message.downcase.include? "factory already
    //      registered"
    //    }
    openproj::seeder::DevelopmentDataSeeder d;
    d.seed();
  }
};
}  // namespace seeder
}  // namespace openproj
