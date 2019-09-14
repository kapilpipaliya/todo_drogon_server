namespace openproject {
class PermittedParams
  namespace AllowedSettings {
    class Restriction
      attr_reader :restricted_keys, :condition

       Restriction(restricted_keys, condition) {
        this->restricted_keys = restricted_keys
        this->condition = condition
      }

       void applicable?() {
        if ( condition.respond_to? :call) {
          condition.call
        else
          condition
        }
      }
    }

    module_function

     void all() {
      keys = Setting.available_settings.keys

      restrictions.select(&:applicable?).each { |restriction|
        restricted_keys = restriction.restricted_keys

        keys.delete_if ( { |key| restricted_keys.include? key }) {
      }

      keys
    }

     void add_restriction!(keys:, condition:) {
      restrictions << Restriction.new(keys, condition)
    }

     void restrictions() {
      this->restrictions ||= []
    }

     void init!() {
      password_keys = %w(
        password_min_length
        password_active_rules
        password_min_adhered_rules
        password_days_valid
        password_count_former_banned
        lost_password
      )

      add_restriction!(
        keys: password_keys,
        condition: -> { OpenProject::Configuration.disable_password_login? }
      )

      add_restriction!(
        keys: %w(registration_footer),
        condition: -> { OpenProject::Configuration.registration_footer.present? }
      )
    }

    init!
  }
}
