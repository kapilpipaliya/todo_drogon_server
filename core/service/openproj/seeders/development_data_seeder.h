class DevelopmentDataSeeder : public CompositeSeeder {
   void data_seeder_classes() {
    [
      DevelopmentData::UsersSeeder,
      DevelopmentData::CustomFieldsSeeder,
      DevelopmentData::ProjectsSeeder,
      //DevelopmentData::WorkPackageSeeder
    ]
  }

   void namespace() {
    'DevelopmentData'
  }
}
