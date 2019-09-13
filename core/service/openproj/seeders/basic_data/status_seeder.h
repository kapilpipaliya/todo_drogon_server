namespace BasicData {
  class StatusSeeder : public Seeder {
     void seed_data!() {
      Status.transaction {
        data.each { |attributes|
          Status.create!(attributes)
        }
      }
    }

     void applicable() {
      Status.all.any?
    }

     void not_applicable_message() {
      'Skipping statuses - already exists/configured'
    }

     void data() {
      raise NotImplementedError
    }
  }
}
