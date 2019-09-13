namespace BasicData {
  class BuiltinRolesSeeder : public Seeder {
     void seed_data!() {
      data.each { |attributes|
        unless Role.find_by(builtin: attributes[:builtin]).nil?
          puts "   *** Skipping built in role #{attributes[:name]} - already exists"
          next
        }

        Role.create(attributes)
      }
    }

     void data() {
      [
        { name: I18n.t(:default_role_non_member), position: 0, builtin: Role::BUILTIN_NON_MEMBER },
        { name: I18n.t(:default_role_anonymous),  position: 1, builtin: Role::BUILTIN_ANONYMOUS  }
      ]
    }
  }
}
