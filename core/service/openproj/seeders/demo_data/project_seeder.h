#pragma once
#include <drogon/drogon.h>
#include <yaml-cpp/yaml.h>
#include "../basic_data/type_seeder.h"
#include "../seeder.h"
#include "group_seeder.h"
#include "iostream"
#include "models/Categories.h"
#include "models/MemberRoles.h"
#include "models/Members.h"
#include "models/News.h"
#include "models/Projects.h"
#include "models/ProjectsTypes.h"
#include "models/Roles.h"
#include "models/Settings.h"
#include "models/Types.h"
#include "models/Users.h"
#include "version_builder.h"
namespace openproj {
namespace seeder {
namespace DemoData {
class ProjectSeeder : public Seeder {
 public:
  // Careful: The seeding recreates the seeded project before it runs, so any
  // changes on the seeded project will be lost.
  YAML::Node seed_projects_overview;
  YAML::Node seed_projects_standard;
  std::string curr_proj;
  void seed_data() {
    //      seed_projects = demo_data_for("projects").keys

    try {
      seed_projects_overview = YAML::LoadFile(
          "./config/locales/en.seeders.standard_overview.yml")["en"]["seeders"]
                                                              ["standard"]
                                                              ["demo_data"];

      seed_projects_standard = YAML::LoadFile(
          "./config/locales/en.seeders.standard.yml")["en"]["seeders"]
                                                     ["standard"]["demo_data"];
    } catch (YAML::BadFile& e) {
      LOG_DEBUG << e.what();
    }
    //      seed_projects.each { |key|
    for (auto it : seed_projects_standard["projects"]) {
      auto key = it.first.as<std::string>();
      LOG_DEBUG << key;
      curr_proj = key;

      LOG_DEBUG << " ↳ Creating " << key << " project...";

      LOG_DEBUG << "   -Creating/Resetting project";
      auto project_id = reset_project(key);

      LOG_DEBUG << "   -Setting members.";
      set_members(project_id);

      LOG_DEBUG << "   -Creating news.";
      seed_news(project_id, key);

      LOG_DEBUG << "   -Assigning types.";
      set_types(project_id, key);

      LOG_DEBUG << "   -Creating categories";
      seed_categories(project_id, key);
      /*
                    LOG_DEBUG << "   -Creating versions.";
                    seed_versions(project_id, key);

                    LOG_DEBUG << "   -Creating queries.";
                    seed_queries(project_id, key);

                    //        project_data_seeders(project, key).each { |seeder|
                    // Todo fix this.
                    // LOG_DEBUG << "   -#{seeder.class.name.demodulize}";
                    //          seeder.seed!
                    //        }
                */
      //        Setting.demo_projects_available = "true"
    }

    LOG_DEBUG << " ↳ Assign groups to projects";
    set_groups();

    LOG_DEBUG << " ↳ Update form configuration with global queries";
    set_form_configuration();

    LOG_DEBUG << " ↳ Updating settings";
    seed_settings();
  }

  bool is_applicable() {
    //      Project.count.zero?
    return true;
  }

  std::vector<std::shared_ptr<seeder::Seeder>> project_data_seeders(
      long project_id, std::string key) {
    //      seeders = [
    //        DemoData::WikiSeeder,
    //        DemoData::CustomFieldSeeder,
    //        DemoData::WorkPackageSeeder,
    //        DemoData::WorkPackageBoardSeeder
    //      ]

    //      seeders.map { |seeder| seeder.new project, key }
  }

  void seed_settings() {
    //      welcome = demo_data_for("welcome")

    //      if ( welcome.present?) {
    //        Setting.welcome_title = welcome[:title]
    //        Setting.welcome_text = welcome[:text]
    //        Setting.welcome_on_homescreen = 1
    //      }
    auto welcome_node = seed_projects_standard["welcome"];
    if (welcome_node.IsDefined()) {
      auto title = welcome_node["title"].as<std::string>();
      auto text = welcome_node["text"].as<std::string>();

      updateSetting("welcome_title", title);
      updateSetting("welcome_text", text);
      updateSetting("welcome_on_homescreen", std::to_string(1));
    }
  }
  void updateSetting(std::string key, std::string value) {
    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::Settings> mapper_settings(
        clientPtr);

    auto result_settings = mapper_settings.findBy(
        (Criteria(drogon_model::openproject6::Settings::Cols::_name,
                  CompareOperator::EQ, key)));
    if (result_settings.size() > 0) {
      auto settings = result_settings.at(0);
      settings.setValue(value);  // text  ;
      settings.setUpdatedOn(
          trantor::Date::now());  // timestamp_without_time_zone  ;
      mapper_settings.update(settings);
    } else {
      LOG_DEBUG << "no rows found for settings table";
    }
  }

  long reset_project(std::string key) {
    delete_project(key);
    return create_project(key);
  }

  long create_project(std::string key) {
    //      Project.create! project_data(key)
    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::Projects> mapper(clientPtr);
    drogon_model::openproject6::Projects project;
    project.setName(key);
    project.setIsPublic(true);  // this is default
    project.setStatus(1);       // This is default
    project.setCreatedOn(trantor::Date::now());
    mapper.insert(project);
    return *project.getId().get();
  }

  void delete_project(std::string key) {
    //      if ( delete_me = find_project(key)) {
    //        delete_me.destroy
    //      }
    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::Projects> mapper(clientPtr);
    mapper.deleteBy(Criteria(drogon_model::openproject6::Projects::Cols::_name,
                             CompareOperator::EQ, key));
  }

  void set_members(long project_id) {
    //      role = Role.find_by(name:
    //      translate_with_base_url(:default_role_project_admin))
    //      user = User.admin.first

    //      Member.create!(
    //        project: project,
    //        principal: user,
    //        roles: [role]
    //      )
    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::Roles> mapper(clientPtr);
    auto role =
        mapper.findBy(Criteria(drogon_model::openproject6::Roles::Cols::_name,
                               CompareOperator::EQ, "Project admin"));

    drogon::orm::Mapper<drogon_model::openproject6::Users> mapper_user(
        clientPtr);
    auto user = mapper_user.findBy(
        Criteria(drogon_model::openproject6::Users::Cols::_admin,
                 CompareOperator::EQ, true));
    drogon::orm::Mapper<drogon_model::openproject6::Members> mapper_member(
        clientPtr);
    drogon_model::openproject6::Members member;
    member.setProjectId(project_id);
    member.setUserId(*user.at(0).getId());
    member.setCreatedOn(trantor::Date::now());
    member.setMailNotification(false);  // this is default
    mapper_member.insert(member);

    drogon::orm::Mapper<drogon_model::openproject6::MemberRoles>
        mapper_member_role(clientPtr);
    drogon_model::openproject6::MemberRoles member_role;
    member_role.setRoleId(*role.at(0).getId());
    member_role.setMemberId(*member.getId());
    mapper_member_role.insert(member_role);
  }

  void set_groups() {
    //      DemoData::GroupSeeder.new.add_projects_to_groups
    openproj::seeder::DemoData::GroupSeeder g;
    g.add_projects_to_groups();
  }

  void set_form_configuration() {
    //      Type.all.each { |type|
    //        BasicData::TypeSeeder.new.set_attribute_groups_for_type(type)
    //      }
    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::Types> mapper_types(
        clientPtr);

    auto result_types =
        mapper_types.orderBy(drogon_model::openproject6::Types::Cols::_id)
            .findAll();

    return;  // because demo_data_for("type_configuration") is nil
    // move set_attribute_groups_for_type from typeseeder class as its abstract
    // class.
    for (auto& it : result_types) {
      //      if ( demo_data_for("type_configuration").nil?) { return ;}

      //      demo_data_for("type_configuration").each { |entry|
      //        if ( entry[:form_configuration] && I18n.t(entry[:type]) ===
      //        type.name) {

      //          entry[:form_configuration].each { |form_config_attr|
      //            groups = type.default_attribute_groups
      //            query_association = "query_" +
      //            find_query_by_name(form_config_attr[:query_name]).to_s
      //            groups.unshift([form_config_attr[:group_name],
      //            [query_association.to_sym]])

      //            type.attribute_groups = groups
      //          }

      //          type.save!
      //        }
      //      }
      auto clientPtr = drogon::app().getDbClient("sce");
      drogon::orm::Mapper<drogon_model::openproject6::Types> mapper_types(
          clientPtr);
      drogon_model::openproject6::Types types;
      //        types.setName();  // character_varying
      //        DEFAULT=""::character_varying
      //                          // NOT_NULL;
      //        types.set "position"();          // integer DEFAULT=1 ;
      //        types.setIsInRoadmap();          // boolean DEFAULT=true
      //        NOT_NULL; types.setIsMilestone();          // boolean
      //        DEFAULT=false NOT_NULL; types.setIsDEFAULT = boolean();  //
      //        DEFAULT=false NOT_NULL ; types.setColorId();              //
      //        integer  ; types.setCreatedAt(
      //            trantor::Date::now());  // timestamp_without_time_zone
      //            NOT_NULL ;
      //        types.setUpdatedAt(
      //            trantor::Date::now());   // timestamp_without_time_zone
      //            NOT_NULL ;
      //        types.setIsStandard();       // boolean DEFAULT=false NOT_NULL;
      //        types.setAttributeGroups();  // text  ;
      //        types.setDescription();      // text  ;

      // mapper_types.update(types);
    }
  }

  void set_types(long project_id, std::string key) {
    //      project.types.clear
    //      Array(project_data_for(key, "types")).each { |type_name|
    //        type = Type.find_by(name: translate_with_base_url(type_name))
    //        project.types << type
    //      }

    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::Types> mapper_types(
        clientPtr);

    for (auto it : seed_projects_standard["projects"][curr_proj]["types"]) {
      drogon_model::openproject6::Types types;
      auto t = it.as<std::string>();
      if (t == ":default_type_task") {
        t = "Task";
      } else if (t == ":default_type_milestone") {
        t = "Milestone";
      } else if (t == ":default_type_phase") {
        t = "Phase";
      } else if (t == ":default_type_feature") {
        t = "Feature";
      } else if (t == ":default_type_bug") {
        t = "Bug";
      } else if (t == ":default_type_epic") {
        t = "Epic";
      } else if (t == ":default_type_user_story") {
        t = "User story";
      } else {
        LOG_DEBUG << "This Must be found " << t;
      }

      auto result_types = mapper_types.findBy(
          (Criteria(drogon_model::openproject6::Types::Cols::_name,
                    CompareOperator::EQ, t)));

      if (result_types.size() > 0) {
        drogon::orm::Mapper<drogon_model::openproject6::ProjectsTypes>
            mapper_projects_types(clientPtr);
        drogon_model::openproject6::ProjectsTypes projects_types;
        projects_types.setProjectId(project_id);
        projects_types.setTypeId(*result_types.at(0).getId());
        mapper_projects_types.insert(projects_types);
      } else {
        LOG_DEBUG << t << "not found";
      }
    }
  }

  void seed_categories(long project_id, std::string key) {
    //      Array(project_data_for(key, "categories")).each { |cat_name|
    //        project.categories.create name: cat_name
    //      }

    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::Categories>
        mapper_categories(clientPtr);

    auto categories_node =
        seed_projects_standard["projects"][curr_proj]["categories"];
    if (categories_node.Type() == YAML::NodeType::Sequence) {
      for (auto it : categories_node) {
        auto t = it.as<std::string>();

        drogon_model::openproject6::Categories categories;
        categories.setName(t);
        categories.setProjectId(project_id);
        categories.setCreatedAt(trantor::Date::now());
        categories.setUpdatedAt(trantor::Date::now());
        mapper_categories.insert(categories);
      }
    }
  }

  void seed_news(long project_id, std::string key) {
    //      Array(project_data_for(key, "news")).each { |news|
    //        News.create! project: project, title: news[:title], summary:
    //        news[:summary], description: news[:description]
    //      }

    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::News> mapper_news(
        clientPtr);
    auto news_yaml = seed_projects_standard["projects"][curr_proj]["news"][0];
    // LOG_DEBUG << it.first.as<std::string>();
    auto title = news_yaml["title"].as<std::string>();
    auto summary = news_yaml["summary"].as<std::string>();
    auto description = news_yaml["description"].as<std::string>();

    drogon_model::openproject6::News news;
    news.setProjectId(project_id);
    news.setTitle(title);
    news.setSummary(summary);
    news.setDescription(description);
    news.setAuthorId(0);       // this is default
    news.setCommentsCount(0);  // This is default
    mapper_news.insert(news);
  }

  void seed_queries(long project_id, std::string key) {
    //      Array(project_data_for(key, "queries")).each { |config|
    //        QueryBuilder.new(config, project).create!
    //      }
  }

  void seed_versions(long project_id, std::string key) {
    //      version_data = Array(project_data_for(key, "versions"))

    //      version_data.each { |attributes|
    //        VersionBuilder.new(attributes, project).create!
    //      }
    auto version_data =
        seed_projects_standard["projects"][curr_proj]["versions"];
    if (version_data.IsDefined()) {
      for (auto it : version_data) {
        openproj::seeder::DemoData::VersionBuilder v(version_data, project_id);
        v.create();
      }
    }
  }

  void seed_board(long project_id) {
    //      Forum.create!(
    //        project: project,
    //        name: demo_data_for("board.name"),
    //        description: demo_data_for("board.description")
    //      )
  }

  //    namespace Data {
  //      module_function

  void project_data(std::string key) {
    //        {
    //          name: project_name(key),
    //          identifier: project_identifier(key),
    //          description: project_description(key),
    //          enabled_module_names: project_modules(key),
    //          types: project_types,
    //          parent_id: parent_project_id(key)
    //        }
  }

  void parent_project_id(std::string key) {
    //        parent_project(key).try(:id)
  }

  void parent_project(std::string key) {
    //        identifier = project_data_for(key, "parent")
    //        return nil unless identifier.present?

    //        Project.find_by(identifier: identifier)
  }

  void project_name(std::string key) {
    //        project_data_for(key, "name")
  }

  void project_identifier(std::string key) {
    //        project_data_for(key, "identifier")
  }

  void project_description(std::string key) {
    //        project_data_for(key, "description")
  }

  void project_types() {
    //        Type.all
    auto clientPtr = drogon::app().getDbClient("sce");

    drogon::orm::Mapper<drogon_model::openproject6::Types> mapper(clientPtr);
    drogon_model::openproject6::Types types;
  }

  void project_modules(std::string key) {
    //        project_data_for(key, "modules")
  }

  void find_project(std::string key) {
    //        Project.find_by(identifier: project_identifier(key))
    //      }
  }

  // include Data
};
}  // namespace DemoData
}  // namespace seeder
}  // namespace openproj
