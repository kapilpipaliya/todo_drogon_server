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
  std::vector<std::pair<std::string, std::string>> data_;

 public:
  SettingSeeder() {
    openproj::models::Setting s;
    for (auto it : s.available_settings) {
      if (it.second.Type() == YAML::NodeType::Map) {
        auto node = it.second["default"];
        YAML::Emitter out;
        out << node;
        data_.push_back({it.first.as<std::string>(), out.c_str()});
        //        switch (node.Type()) {
        //          case YAML::NodeType::Map:
        //          case YAML::NodeType::Sequence:
        //            break;
        //          case YAML::NodeType::Null:
        //          case YAML::NodeType::Undefined:
        //            data_.push_back({it.first.as<std::string>(), ""});
        //            break;
        //          case YAML::NodeType::Scalar:
        //            data_.push_back(
        //                {it.first.as<std::string>(), node.as<std::string>()});
        //            break;
        //        }
      }
    }
    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::Roles> mapper(clientPtr);
    auto role =
        mapper.findBy(Criteria(drogon_model::openproject6::Roles::Cols::_name,
                               CompareOperator::EQ, "Project admin"));
    if (!role.empty()) {
      auto role_id = *role.at(0).getId();
      update_unless_present("new_project_user_role_id",
                            std::to_string(role_id));
    }

    drogon::orm::Mapper<drogon_model::openproject6::Statuses> mapper_status(
        clientPtr);
    auto status = mapper_status.findBy(
        Criteria(drogon_model::openproject6::Statuses::Cols::_name,
                 CompareOperator::EQ, "Closed"));
    if (status.size() > 0) {
      auto status_id = *status.at(0).getId();
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
    for (auto it : settings_not_in_db()) {
      // auto data = data_[it];
      // on setting.h reimplemented []= operator
      // std::cout << it.first << ": " << it.second << std::endl;

      auto clientPtr = drogon::app().getDbClient("sce");
      drogon::orm::Mapper<drogon_model::openproject6::Settings> mapper(
          clientPtr);
      drogon_model::openproject6::Settings setting;
      setting.setName(it.first);
      setting.setValue(it.second);
      setting.setUpdatedOn(trantor::Date::now());
      mapper.insert(setting);
    }
  }

  bool applicable() {
    //      !settings_not_in_db.empty?
    return true;
  }

  void not_applicable_message() {
    //      'Skipping settings as all settings already exist in the db'
  }

  std::vector<std::pair<std::string, std::string>> data() {
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
    auto indb = settings_in_db();
    if (std::find(indb.begin(), indb.end(), key) != indb.end()) {
      if (!value.empty()) {
        auto find = std::find_if(data_.begin(), data_.end(),
                                 [key](std::pair<std::string, std::string> &p) {
                                   return p.first == key;
                                 });
        if (find == data_.end()) {
          data_.push_back({key, value});
        } else {
          find->second = value;
        }
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

  std::vector<std::pair<std::string, std::string>> settings_not_in_db() {
    //      data().keys - settings_in_db();
    std::vector<std::pair<std::string, std::string>> result;
    auto indb = settings_in_db();
    for (auto &it2 : data_) {
      auto find =
          std::find_if(indb.begin(), indb.end(),
                       [&it2](std::string &p) { return p == it2.first; });
      if (find == indb.end()) {
        result.push_back(it2);
      }
    }
    return result;
  }
};
}  // namespace BasicData
}  // namespace seeder
}  // namespace openproj
