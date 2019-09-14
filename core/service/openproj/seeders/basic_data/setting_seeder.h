namespace BasicData {
  class SettingSeeder : public Seeder {
     void seed_data!() {
      Setting.transaction {
        settings_not_in_db.each { |setting_name|
          datum = data[setting_name]

          Setting[setting_name.to_sym] = datum
        }
      }
    }

     void applicable?() {
      !settings_not_in_db.empty?
    }

     void not_applicable_message() {
      'Skipping settings as all settings already exist in the db'
    }

     void data() {
      this->settings ||= begin
        settings = Setting.available_settings.each_with_object({}) { |(k, v), hash|
          hash[k] = v['default'] || ''
        }

        // deviate from the defaults specified in settings.yml here
        // to set a default role. The role cannot be specified in the settings.yml as
        // that would mean to know the ID upfront.
        update_unless_present(settings, 'new_project_user_role_id') {
          Role.find_by(name: I18n.t(:default_role_project_admin)).try(:id)
        }

        // Set the closed status for repository commit references
        update_unless_present(settings, 'commit_fix_status_id') {
          Status.find_by(name: I18n.t(:default_status_closed)).try(:id)
        }

        settings
      }
    }

    private:

     void update_unless_present(settings, key) {
      if ( !settings_in_db.include?(key)) {
        value = yield
        settings[key] = value unless value.nil?
      }
    }

     void settings_in_db() {
      this->settings_in_db ||= Setting.all.pluck(:name)
    }

     void settings_not_in_db() {
      data.keys - settings_in_db
    }
  }
}
