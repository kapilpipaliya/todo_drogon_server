#pragma once
#include <drogon/drogon.h>

namespace openproj {
namespace seeder {
class Seeder {
 public:
  virtual void seed() {
    if (applicable()) {
      seed_data();
    } else {
      LOG_DEBUG << "   *** #{not_applicable_message}";
    }
  }
  virtual void seed_data() = 0;
  virtual bool applicable() { return true; }
  virtual void not_applicable_message() {
    LOG_DEBUG << "Skipping #{this->class.name}";
  }

 protected:
  //
  // Translate the given string with the fixed interpolation for base_url
  // Deep interpolation is required in order for interpolations on hashes to
  // work!
  void translate_with_base_url(std::string str) {
    //    I18n.t(str, deep_interpolation: true, base_url:
    //    OpenProject::Configuration.rails_relative_url_root)
  }

  void edition_data_for(std::string key) {
    //    data =
    //    translate_with_base_url("seeders.#{OpenProject::Configuration['edition']}.#{key}")

    //    if ( data.is_a?(String) && data.start_with?("translation missing")) {
    //    return nil ;}

    //    data
  }
  void demo_data_for(std::string key) { edition_data_for("demo_data." + key); }
  void project_data_for(std::string project, std::string key) {
    demo_data_for("projects." + project + "." + key);
  }
  void project_has_data_for(std::string project, std::string key) {
    //    I18n.exists?("seeders.#{OpenProject::Configuration['edition']}.demo_data.projects.#{project}.#{key}")
  }
};
}  // namespace seeder
}  // namespace openproj
