namespace openproj {
class Seeder
   void seed!() {
    if ( applicable?) {
      seed_data!
    else
      puts "   *** #{not_applicable_message}"
    }
  }

   void seed_data!() {
    raise NotImplementedError
  }

   void applicable?() {
    true
  }

   void not_applicable_message() {
    "Skipping #{this->class.name}"
  }

  protected:

  //
  // Translate the given string with the fixed interpolation for base_url
  // Deep interpolation is required in order for interpolations on hashes to work!
   void translate_with_base_url(string) {
    I18n.t(string, deep_interpolation: true, base_url: OpenProject::Configuration.rails_relative_url_root)
  }

   void edition_data_for(key) {
    data = translate_with_base_url("seeders.#{OpenProject::Configuration['edition']}.#{key}")

    if ( data.is_a?(String) && data.start_with?("translation missing")) { return nil ;}

    data
  }

   void demo_data_for(key) {
    edition_data_for("demo_data.#{key}")
  }

   void project_data_for(project, key) {
    demo_data_for "projects.#{project}.#{key}"
  }

   void project_has_data_for?(project, key) {
    I18n.exists?("seeders.#{OpenProject::Configuration['edition']}.demo_data.projects.#{project}.#{key}")
  }
}
