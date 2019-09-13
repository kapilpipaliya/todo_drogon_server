namespace StandardSeeder {
  class BasicDataSeeder : public ::BasicDataSeeder {
     void data_seeder_classes() {
      [
        ::BasicData::BuiltinRolesSeeder,
        ::BasicData::RoleSeeder,
        ::StandardSeeder::BasicData::ActivitySeeder,
        ::BasicData::ColorSeeder,
        ::BasicData::ColorSchemeSeeder,
        ::StandardSeeder::BasicData::WorkflowSeeder,
        ::StandardSeeder::BasicData::PrioritySeeder,
        ::BasicData::SettingSeeder
      ]
    }
  }
}
