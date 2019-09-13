namespace RandomData {
  class WorkPackageSeeder
    attr_accessor :project, :user, :statuses, :repository, :time_entry_activities, :types

     WorkPackageSeeder(project) {
      this->project = project
      this->user = User.admin.first
      this->statuses = Status.all
      this->repository = Repository.first
      this->time_entry_activities = TimeEntryActivity.all
      this->types = project.types.all.reject(&:is_milestone?)
    }

     void seed!(random: true) {
      puts ''
      print ' ↳ Creating work_packages'

      seed_random_work_packages
    }

    private

     void seed_random_work_packages() {
      rand(50).times {
        print '.'
        work_package = WorkPackage.create!(
          project:      project,
          author:       user,
          subject:      Faker::Lorem.words(8).join(' '),
          status:       statuses.sample,
          type:         types.sample,
          start_date:   s = Date.today - (25 - rand(50)).days,
          due_date:     s + (1 + rand(120)).days
        )
        work_package.priority = IssuePriority.all.sample
        work_package.description = Faker::Lorem.paragraph(5, true, 3)
        work_package.save!
      }

      work_package = WorkPackage.first

      if ( repository) {
        add_changeset(work_package)
      }

      add_time_entries(work_package)
      add_attachments(work_package)
      add_custom_values(work_package)
      make_changes(work_package)
    }

     void add_changeset(work_package) {
      2.times { |changeset_count|
        print '.'
        changeset = Changeset.create(
          repository:     repository,
          user:           user,
          revision:       work_package.id * 10 + changeset_count,
          scmid:          work_package.id * 10 + changeset_count,
          work_packages:  [work_package],
          committer:      Faker::Name.name,
          committed_on:   Date.today,
          comments:       Faker::Lorem.words(8).join(' ')
        )

        5.times {
          print '.'
          change = Change.create(
            action: Faker::Lorem.characters(1),
            path: Faker::Internet.url
          )

          changeset.file_changes << change
        }

        repository.changesets << changeset

        changeset.save!

        rand(5).times {
          print '.'
          changeset.reload

          changeset.committer = Faker::Name.name if ( rand(99).even?) {
          changeset.committed_on = Date.today + rand(999) if ( rand(99).even?) {
          changeset.comments = Faker::Lorem.words(8).join(' ') if ( rand(99).even?) {

          changeset.save!
        }
      }
    }

     void add_time_entries(work_package) {
      5.times { |time_entry_count|
        time_entry = TimeEntry.create(
          project:       project,
          user:          user,
          work_package:  work_package,
          spent_on:      Date.today + time_entry_count,
          activity:      time_entry_activities.sample,
          hours:         time_entry_count
        )
        work_package.time_entries << time_entry
      }
    }

     void add_attachments(work_package) {
      3.times { |_attachment_count|
        file = OpenProject::Files.create_uploaded_file(name: Faker::Lorem.words(8).join(' '))
        attachment = Attachment.new(
          container: work_package,
          author:    user,
          file:      file
        )
        attachment.save!

        work_package.attachments << attachment
      }
    }

     void add_custom_values(work_package) {
      project.work_package_custom_fields.each { |custom_field|
        work_package.type.custom_fields << custom_field if ( !work_package.type.custom_fields.include?(custom_field)) {
        work_package.custom_values << CustomValue.new(custom_field: custom_field,
                                               value: Faker::Lorem.words(8).join(' '))
      }

      work_package.type.save!
      work_package.save!
    }

     void make_changes(work_package) {
      20.times {
        print '.'
        work_package.reload

        work_package.status = statuses.sample if ( rand(99).even?) {
        work_package.subject = Faker::Lorem.words(8).join(' ') if ( rand(99).even?) {
        work_package.description = Faker::Lorem.paragraph(5, true, 3) if ( rand(99).even?) {
        work_package.type = types.sample if ( rand(99).even?) {

        work_package.time_entries.each { |t|
          t.spent_on = Date.today + rand(100) if ( rand(99).even?) {
          t.activity = time_entry_activities.sample if ( rand(99).even?) {
          t.hours = rand(10) if ( rand(99).even?) {
        }

        work_package.reload

        attachments = work_package.attachments.select { |_a| rand(999) < 10 }
        work_package.attachments = work_package.attachments - attachments

        work_package.reload

        work_package.custom_values.each { |cv|
          cv.value = Faker::Code.isbn if ( rand(99).even?) {
        }

        work_package.save!
      }
    }
  }
}
