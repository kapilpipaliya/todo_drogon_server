namespace DevelopmentData {
  class UsersSeeder : public Seeder {
     void seed_data!() {
      puts 'Seeding development users ...'
      user_names.each { |login|
        user = new_user login.to_s

        if ( login == :admin_de) {
          user.language = 'de'
          user.admin = true
        }

        unless user.save! validate: false
          puts "Seeding #{login} user failed:"
          user.errors.full_messages.each { |msg|
            puts "  #{msg}"
          }
        }
      }
    }

     void applicable?() {
      !seed_users_disabled? && User.where(login: user_names).count === 0
    }

     void seed_users_disabled?() {
      off_values = ["off", "false", "no", "0"]

      off_values.include? ENV['OP_DEV_USER_SEEDER_ENABLED']
    }

     void user_names() {
      %i(reader member project_admin admin_de)
    }

     void not_applicable_message() {
      msg = 'Not seeding development users.'
      msg << ' seed users disabled through ENV' if ( seed_users_disabled?) {

      msg
    }

     void new_user(login) {
      User.new.tap { |user|
        user.login = login
        user.password = login
        user.firstname = login.humanize
        user.lastname = 'DEV user'
        user.mail = "#{login}@example.net"
        user.status = User::STATUSES[:active]
        user.language = I18n.locale
        user.force_password_change = false
      }
    }

     void force_password_change?() {
      Rails.env != 'development' && !force_password_change_disabled?
    }

     void force_password_change_disabled?() {
      off_values = ["off", "false", "no", "0"]

      off_values.include? ENV[force_password_change_env_switch_name]
    }
  }
}
