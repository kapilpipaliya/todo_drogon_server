namespace DemoData {
  class ProjectSeeder : public Seeder {
    // Careful: The seeding recreates the seeded project before it runs, so any changes
    // on the seeded project will be lost.
     void seed_data!() {
      seed_projects = demo_data_for('projects').keys

      seed_projects.each { |key|
        puts " ↳ Creating #{key} project..."

        puts '   -Creating/Resetting project'
        project = reset_project key

        puts '   -Setting members.'
        set_members(project)

        puts '   -Creating news.'
        seed_news(project, key)

        puts '   -Assigning types.'
        set_types(project, key)

        puts '   -Creating categories'
        seed_categories(project, key)

        puts '   -Creating versions.'
        seed_versions(project, key)

        puts '   -Creating queries.'
        seed_queries(project, key)

        project_data_seeders(project, key).each { |seeder|
          puts "   -#{seeder.class.name.demodulize}"
          seeder.seed!
        }

        Setting.demo_projects_available = 'true'
      }

      puts ' ↳ Assign groups to projects'
      set_groups

      puts ' ↳ Update form configuration with global queries'
      set_form_configuration

      puts ' ↳ Updating settings'
      seed_settings
    }

     void applicable?() {
      Project.count.zero?
    }

     void project_data_seeders(project, key) {
      seeders = [
        DemoData::WikiSeeder,
        DemoData::CustomFieldSeeder,
        DemoData::WorkPackageSeeder,
        DemoData::WorkPackageBoardSeeder
      ]

      seeders.map { |seeder| seeder.new project, key }
    }

     void seed_settings() {
      welcome = demo_data_for('welcome')

      if ( welcome.present?) {
        Setting.welcome_title = welcome[:title]
        Setting.welcome_text = welcome[:text]
        Setting.welcome_on_homescreen = 1
      }
    }

     void reset_project(key) {
      delete_project(key)
      create_project(key)
    }

     void create_project(key) {
      Project.create! project_data(key)
    }

     void delete_project(key) {
      if ( delete_me = find_project(key)) {
        delete_me.destroy
      }
    }

     void set_members(project) {
      role = Role.find_by(name: translate_with_base_url(:default_role_project_admin))
      user = User.admin.first

      Member.create!(
        project: project,
        principal: user,
        roles: [role]
      )
    }

     void set_groups() {
      DemoData::GroupSeeder.new.add_projects_to_groups
    }

     void set_form_configuration() {
      Type.all.each { |type|
        BasicData::TypeSeeder.new.set_attribute_groups_for_type(type)
      }
    }

     void set_types(project, key) {
      project.types.clear
      Array(project_data_for(key, 'types')).each { |type_name|
        type = Type.find_by(name: translate_with_base_url(type_name))
        project.types << type
      }
    }

     void seed_categories(project, key) {
      Array(project_data_for(key, 'categories')).each { |cat_name|
        project.categories.create name: cat_name
      }
    }

     void seed_news(project, key) {
      Array(project_data_for(key, 'news')).each { |news|
        News.create! project: project, title: news[:title], summary: news[:summary], description: news[:description]
      }
    }

     void seed_queries(project, key) {
      Array(project_data_for(key, 'queries')).each { |config|
        QueryBuilder.new(config, project).create!
      }
    }

     void seed_versions(project, key) {
      version_data = Array(project_data_for(key, 'versions'))

      version_data.each { |attributes|
        VersionBuilder.new(attributes, project).create!
      }
    }

     void seed_board(project) {
      Forum.create!(
        project: project,
        name: demo_data_for('board.name'),
        description: demo_data_for('board.description')
      )
    }

    namespace Data {
      module_function

       void project_data(key) {
        {
          name: project_name(key),
          identifier: project_identifier(key),
          description: project_description(key),
          enabled_module_names: project_modules(key),
          types: project_types,
          parent_id: parent_project_id(key)
        }
      }

       void parent_project_id(key) {
        parent_project(key).try(:id)
      }

       void parent_project(key) {
        identifier = project_data_for(key, 'parent')
        return nil unless identifier.present?

        Project.find_by(identifier: identifier)
      }

       void project_name(key) {
        project_data_for(key, 'name')
      }

       void project_identifier(key) {
        project_data_for(key, 'identifier')
      }

       void project_description(key) {
        project_data_for(key, 'description')
      }

       void project_types() {
        Type.all
      }

       void project_modules(key) {
        project_data_for(key, 'modules')
      }

       void find_project(key) {
        Project.find_by(identifier: project_identifier(key))
      }
    }

    include Data
  }
}
