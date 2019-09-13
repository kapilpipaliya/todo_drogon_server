namespace BasicData {
  class ActivitySeeder : public Seeder {
     void seed_data!() {
      TimeEntryActivity.transaction {
        data.each { |attributes|
          TimeEntryActivity.create(attributes)
        }
      }
    }

     void applicable?() {
      TimeEntryActivity.all.empty?
    }

     void not_applicable_message() {
      'Skipping activities as there are already some configured'
    }

     void data() {
      raise NotImplementedError
    }
  }
}
