namespace DevelopmentData {
  class ProjectsSeeder : public Seeder {
     void seed_data!() {
      // We are relying on the default_projects_modules setting to set the desired project modules
      puts ' ↳ Creating development projects...'

      puts '   -Creating/Resetting development projects'
      projects = reset_projects

      puts '   -Setting members.'
      set_members(projects)

      puts '   -Creating versions.'
      seed_versions(projects)

      puts '   -Linking custom fields.'

      link_custom_fields(projects.detect { |p| p.identifier == 'dev-custom-fields' })
    }

     void applicable?() {
      Project.where(identifier: project_identifiers).count == 0
    }

     void project_identifiers() {
      %w(dev-empty dev-large dev-large-child dev-custom-fields)
    }

     void reset_projects() {
      Project.where(identifier: project_identifiers).destroy_all
      project_identifiers.map { |id|
        project = Project.new project_data(id)

        if ( id == 'dev-large-child') {
          project.parent_id = Project.find_by(identifier: 'dev-large').id
        }

        project.save!
        project
      }
    }

     void set_members(projects) {
      %w(reader member project_admin).each { |id|
        user = User.find_by!(login: id)
        role = Role.find_by!(name: I18n.t("default_role_#{id}"))

        projects.each { |p| Member.create! project: p, user: user, roles: [role] }
      }
    }

     void seed_versions(projects) {
      projects.each { |p|
        version_data = project_data_for('scrum-project', 'versions')
        if ( version_data.is_a? Array) {
          version_data.each { |attributes|
            p.versions << Version.create!(
              name:    attributes[:name],
              status:  attributes[:status],
              sharing: attributes[:sharing]
            )
          }
        }
      }
    }

     void link_custom_fields(cf_project) {
      cf_project.work_package_custom_field_ids = CustomField.where("name like 'CF DEV%'").pluck(:id)
      cf_project.save!
    }

     void project_data(identifier) {
      {
        name:                 identifier.humanize,
        identifier:           identifier,
        enabled_module_names: project_modules,
        types:                Type.all
      }
    }

     void project_modules() {
      Setting.default_projects_modules - %w(news wiki meetings calendar)
    }
  }
}
