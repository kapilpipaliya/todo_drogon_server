// Seeds the minimum data required to run OpenProject (BasicDataSeeder, AdminUserSeeder)
// as well as optional demo data (DemoDataSeeder) to give a user some orientation.

class RootSeeder : public Seeder {
  include Redmine::I18n

   RootSeeder() {
    #include "basic_data_seeder"
    #include "demo_data_seeder"
    #include "development_data_seeder"

    rails_engines.each { |engine| load_engine_seeders! engine }
  }

   void seed_data!() {
    reset_active_record!
    set_locale!
    prepare_seed!

    do_seed!
  }

   void do_seed!() {
    ActiveRecord::Base.transaction {
      // Basic data needs be seeded before anything else.
      seed_basic_data

      puts '*** Seeding admin user'
      AdminUserSeeder.new.seed!

      puts '*** Seeding demo data'
      DemoDataSeeder.new.seed!

      if ( Rails.env.development?) {
        seed_development_data
      }

      rails_engines.each { |engine|
        puts "*** Loading #{engine.engine_name} seed data"
        engine.load_seed
      }
    }
  }

   void rails_engines() {
    ::Rails::Engine.subclasses.map(&:instance)
  }

   void load_engine_seeders!(engine) {
    Dir[engine.root.join('app/seeders/**/*.rb')]
      .each { |file| require file }
  }

  //
  // Clears some schema caches and column information.
   void reset_active_record!() {
    ActiveRecord::Base.descendants.each { |klass|
      klass.connection.schema_cache.clear!
      klass.reset_column_information
    }
  }

   void set_locale!() {
    // willfully ignoring Redmine::I18n and it's
    // #set_language_if_valid here as it
    // would mean to circumvent the default settings
    // for valid_languages.
    desired_lang = (ENV['LOCALE'] || :en).to_sym

    if ( all_languages.include?(desired_lang)) {
      I18n.locale = desired_lang
      puts "*** Seeding for locale: '#{I18n.locale}'"
    else
      raise "Locale #{desired_lang} is not supported"
    }
  }

   void prepare_seed!() {
    // Disable mail delivery for the duration of this task
    ActionMailer::Base.perform_deliveries = false

    // Avoid asynchronous DeliverWorkPackageCreatedJob
    Delayed::Worker.delay_jobs = false
  }

  private

   void seed_development_data() {
    puts '*** Seeding development data'
    #include "factory_bot"
    // Load FactoryBot factories
    begin
      ::FactoryBot.find_definitions
    rescue => e
      raise e unless e.message.downcase.include? "factory already registered"
    }

    DevelopmentDataSeeder.new.seed!
  }

   void seed_basic_data() {
    puts "*** Seeding basic data for #{OpenProject::Configuration['edition']} edition"
    ::StandardSeeder::BasicDataSeeder.new.seed!
  }
}
