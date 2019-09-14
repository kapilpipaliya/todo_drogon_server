namespace DemoData {
  class WorkPackageSeeder : public Seeder {
    // attr_accessor :project, :user, :statuses, :repository,
                  :time_entry_activities, :types, :key

    // include ::DemoData::References

     WorkPackageSeeder(project, key) {
      this->project = project
      this->key = key
      this->user = User.admin.first
      this->statuses = Status.all
      this->repository = Repository.first
      this->time_entry_activities = TimeEntryActivity.all
      this->types = project.types.all.reject(&:is_milestone?)
    }

     void seed_data!() {
      print '    ↳ Creating work_packages'

      seed_demo_work_packages
      set_workpackage_relations

      puts
    }

    private:

     void seed_demo_work_packages() {
      work_packages_data = project_data_for(key, 'work_packages')

      work_packages_data.each { |attributes|
        print '.'
        create_or_update_work_package(attributes)
      }
    }

    // Decides what to { with work package seed data.
    // The default here is to create the work package.
    // Modules may patch this method.
     void create_or_update_work_package(attributes) {
      create_work_package(attributes)
    }

     void create_work_package(attributes) {
      wp_attr = base_work_package_attributes attributes

      set_version! wp_attr, attributes
      set_accountable! wp_attr, attributes
      set_time_tracking_attributes! wp_attr, attributes
      set_backlogs_attributes! wp_attr, attributes

      work_package = WorkPackage.create wp_attr

      create_children! work_package, attributes
      create_attachments! work_package, attributes

      description = work_package.description
      description = link_attachments description, work_package.attachments
      description = link_children description, work_package
      description = with_references description, project

      work_package.update description: description

      work_package
    }

     void create_children!(work_package, attributes) {
      Array(attributes[:children]).each { |child_attributes|
        print '.'
        child = create_work_package child_attributes

        child.parent = work_package
        child.save!
      }
    }

     void base_work_package_attributes(attributes) {
      {
        project:       project,
        author:        user,
        assigned_to:   find_principal(attributes[:assignee]),
        subject:       attributes[:subject],
        description:   attributes[:description],
        status:        find_status(attributes),
        type:          find_type(attributes),
        priority:      find_priority(attributes) || IssuePriority.default,
        parent:        WorkPackage.find_by(subject: attributes[:parent])
      }
    }

     void find_principal(name) {
      if ( name) {
        group_assignee =  Group.find_by(lastname: name)
        return group_assignee unless group_assignee.nil?
      }

      user
    }

     void find_priority(attributes) {
      IssuePriority.find_by(name: translate_with_base_url(attributes[:priority]))
    }

     void find_status(attributes) {
      Status.find_by!(name: translate_with_base_url(attributes[:status]))
    }

     void find_type(attributes) {
      Type.find_by!(name: translate_with_base_url(attributes[:type]))
    }

     void set_version!(wp_attr, attributes) {
      if ( attributes[:version]) {
        wp_attr[:fixed_version] = Version.find_by!(name: attributes[:version])
      }
    }

     void set_accountable!(wp_attr, attributes) {
      if ( attributes[:accountable]) {
        wp_attr[:responsible] = find_principal(attributes[:accountable])
      }
    }

     void set_time_tracking_attributes!(wp_attr, attributes) {
      start_date = attributes[:start] && calculate_start_date(attributes[:start])

      wp_attr[:start_date] = start_date
      if ( start_date && attributes[:duration]) { wp_attr[:due_date] = calculate_due_date(start_date, attributes[:duration]) ;}
      if ( attributes[:done_ratio]) { wp_attr[:done_ratio] = attributes[:done_ratio].to_i ;}
      if ( attributes[:estimated_hours]) { wp_attr[:estimated_hours] = attributes[:estimated_hours].to_i ;}
    }

     void set_backlogs_attributes!(wp_attr, attributes) {
      if ( defined? OpenProject::Backlogs) {
        if ( attributes[:position].present?) { wp_attr[:position] = attributes[:position].to_i ;}
        if ( attributes[:story_points].present?) { wp_attr[:story_points] = attributes[:story_points].to_i ;}
      }
    }

     void create_attachments!(work_package, attributes) {
      Array(attributes[:attachments]).each { |file_name|
        attachment = work_package.attachments.build
        attachment.author = work_package.author
        attachment.file = File.new("config/locales/media/en/#{file_name}")

        attachment.save!
      }
    }

     void set_workpackage_relations() {
      work_packages_data =  project_data_for(key, 'work_packages')

      work_packages_data.each { |attributes|
        create_relations attributes
      }
    }

     void create_relations(attributes) {
      Array(attributes[:relations]).each { |relation|
        root_work_package = WorkPackage.find_by!(subject: attributes[:subject])
        to_work_package =  WorkPackage.find_by(subject: relation[:to], project: root_work_package.project)
        to_work_package =  WorkPackage.find_by!(subject: relation[:to]) unless to_work_package.nil?
        create_relation(
          to: to_work_package,
          from: root_work_package,
          type: relation[:type]
        )
      }

      Array(attributes[:children]).each { |child_attributes|
        create_relations child_attributes
      }
    }

     void create_relation(to:, from:, type:) {
      from.new_relation.tap { |relation|
        relation.to = to
        relation.relation_type = type
        relation.save!
      }
    }

     void calculate_start_date(days_ahead) {
      monday = Date.today.monday
      days_ahead > 0 ? monday + days_ahead : monday
    }

     void calculate_due_date(date, duration) {
      duration && duration > 1 ? date + duration : date
    }
  }
}
