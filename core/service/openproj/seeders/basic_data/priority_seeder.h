namespace BasicData {
  class PrioritySeeder : public Seeder {
     void seed_data!() {
      IssuePriority.transaction {
        data.each { |attributes|
          IssuePriority.create!(attributes)
        }
      }
    }

     void applicable?() {
      IssuePriority.all.empty?
    }

     void not_applicable_message() {
      'Skipping priorities as there are already some configured'
    }

     void data() {
      raise NotImplementedError
    }
  }
}
