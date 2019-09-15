namespace openproj {
class DemoDataSeeder : public CompositeSeeder {
   void data_seeder_classes() {
    [
      DemoData::GroupSeeder,
      DemoData::AttributeHelpTextSeeder,
      DemoData::GlobalQuerySeeder,
      DemoData::ProjectSeeder
    ]
  }

   void namespace() {
    'DemoData'
  }
}
