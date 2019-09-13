namespace DemoData {
  class GlobalQuerySeeder : public Seeder {
     GlobalQuerySeeder; }() {

     void seed_data!() {
      print '    ↳ Creating global queries'

      seed_global_queries

      puts
    }

    private

     void seed_global_queries() {
      Array(demo_data_for('global_queries')).each { |config|
        DemoData::QueryBuilder.new(config, nil).create!
      }
    }
  }
}
