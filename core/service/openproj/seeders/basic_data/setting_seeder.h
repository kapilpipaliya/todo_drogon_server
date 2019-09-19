#pragma once
#include <drogon/drogon.h>
#include <yaml-cpp/yaml.h>
#include <algorithm>
#include <string>
#include <vector>
#include "../../models/setting.h"
#include "../seeder.h"
#include "models/Roles.h"
#include "models/Settings.h"
#include "models/Statuses.h"

namespace openproj {
namespace seeder {
namespace BasicData {
class SettingSeeder : public Seeder {
  std::map<std::string, std::string> data_;

 public:
  SettingSeeder() {
    openproj::models::Setting s;
    for (auto it : s.available_settings) {
      // data_.push_back({it.first.as<std::string>(),
      // it.second["default"].as<std::string>()});
      data_[it.first.as<std::string>()] =
          it.second["default"].as<std::string>();
    }
    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::Roles> mapper(clientPtr);
    auto r = mapper.findBy(
        Criteria(drogon_model::openproject6::Roles::Cols::_name,
                 CompareOperator::EQ, "Project admin"));
    auto role_id = *r.at(0).getId();
    if (!r.empty()) {
      update_unless_present("new_project_user_role_id", std::to_string(role_id));
    }

    drogon::orm::Mapper<drogon_model::openproject6::Statuses> mapper_status(clientPtr);
    auto status = mapper_status.findBy(
          Criteria(drogon_model::openproject6::Statuses::Cols::_name,
                   CompareOperator::EQ, "Closed"));
    auto status_id = *status.at(0).getId();
    if (!r.empty()) {
      update_unless_present("commit_fix_status_id", std::to_string(status_id));
    }
  }
  void seed_data() {
    //      Setting.transaction {
    //        settings_not_in_db.each { |setting_name|
    //          datum = data[setting_name]

    //          Setting[setting_name.to_sym] = datum
    //        }
    //      }

    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::Settings> mapper(clientPtr);
    for (auto &it : settings_not_in_db()) {
      auto data = data_[it];
    }
  }

  bool applicable() {
    //      !settings_not_in_db.empty?
  }

  void not_applicable_message() {
    //      'Skipping settings as all settings already exist in the db'
  }

  std::map<std::string, std::string> data() {
    //      this->settings ||= begin
    //        settings = Setting.available_settings.each_with_object({}) { |(k,
    //        v), hash|
    //          hash[k] = v['default'] || ''
    //        }

    //        // deviate from the defaults specified in settings.yml here
    //        // to set a default role. The role cannot be specified in the
    //        settings.yml as
    //        // that would mean to know the ID upfront.
    //        update_unless_present(settings, 'new_project_user_role_id') {
    //          Role.find_by(name: I18n.t(:default_role_project_admin)).try(:id)
    //        }

    //        // Set the closed status for repository commit references
    //        update_unless_present(settings, 'commit_fix_status_id') {
    //          Status.find_by(name: I18n.t(:default_status_closed)).try(:id)
    //        }

    //        settings
    //      }

    // moved to constructor
    return data_;
  }

 private:
  void update_unless_present(std::string key, std::string value) {
    //      if ( !settings_in_db.include?(key)) {
    //        value = yield
    //        settings[key] = value unless value.nil?
    //      }
    if (std::find(settings_in_db().begin(), settings_in_db().end(), key) !=
        settings_in_db().end()) {
      if (!value.empty()) {
        data_[key] = value;
      }
    }
  }

  std::vector<std::string> settings_in_db() {
    //      this->settings_in_db ||= Setting.all.pluck(:name)
    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::Settings> mapper(clientPtr);
    auto r = mapper.findAll();
    std::vector<std::string> a;
    for (auto it : r) {
      a.push_back(*it.getName().get());
    }
    return a;
  }

  std::vector<std::string> settings_not_in_db() {
    //      data().keys - settings_in_db();
    std::vector<std::string> result;
    auto indb = settings_in_db();
    for (auto &it2 : indb) {
      if (!data_.contains(it2)) {
        result.push_back(it2);
      }
    }
    return result;
  }
};
}  // namespace BasicData
}  // namespace seeder
}  // namespace openproj
