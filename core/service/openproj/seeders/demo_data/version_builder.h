#pragma once
#include <drogon/drogon.h>
#include <yaml-cpp/yaml.h>
#include "models/Versions.h"
#include "models/WikiPages.h"
namespace openproj {
namespace seeder {
namespace DemoData {
class VersionBuilder {
 public:
  // include ::DemoData::References

  //    attr_reader :config
  //    attr_reader :project
  YAML::Node config;
  long project_id;
  YAML::Node version_node;

  VersionBuilder(YAML::Node &config, long project_id) {
    this->config = config;
    this->project_id = project_id;
  }

  void create() {
    if (valid()) {
      create_version();
    }
  }

 private:
  bool valid() { return true; }

  void create_version() {
    //      new_version().tap { |version|
    //        project.versions << version
    //      }
    new_version();
  }

  long new_version() {
    //      version = Version.create!(
    //        name:    config[:name],
    //        status:  config[:status],
    //        sharing: config[:sharing],
    //        project: project
    //      )

    //      if ( config[:wiki]) { set_wiki! version, config[:wiki] ;}

    //      version

    auto name = config["name"].as<std::string>();
    auto status = config["status"].as<std::string>();
    auto sharing = config["sharing"].as<std::string>();

    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::Versions> mapper_versions(
        clientPtr);
    drogon_model::openproject6::Versions versions;

    versions.setName(
        name);  // character_varying DEFAULT=''::character_varying NOT_NULL;
    versions.setProjectId(project_id);
    versions.setDescription(
        "");  // character_varying DEFAULT=''::character_varying ;
    versions.setEffectiveDate(trantor::Date::now());  // date  ;
    versions.setCreatedOn(
        trantor::Date::now());  // timestamp_without_time_zone  ;
    versions.setUpdatedOn(
        trantor::Date::now());  // timestamp_without_time_zone  ;
    // versions.setWikiPageTitle(); //character_varying  ;
    versions.setStatus(
        status);  // character_varying DEFAULT='open'::character_varying ;
    versions.setSharing(
        sharing);  // character_varying
                   // DEFAULT='none'::character_varying NOT_NULL;
    versions.setStartDate(trantor::Date::now());  // date  ;
    if (config["wiki"]) {
      auto wiki_page_title = config["wiki"]["title"].as<std::string>();
      versions.setWikiPageTitle(wiki_page_title);
    }
    auto version_id = *versions.getId().get();
    mapper_versions.insert(versions);
    if (config["wiki"]) {
      //       oh i dont know hot to get wiki id?
      // set_wiki(version_id, config["wiki"]);
    }
    return version_id;
  }

  void set_wiki(int version_id, YAML::Node config) {
    //           version.wiki_page_title = config[:title]
    //           page = WikiPage.create! wiki: version.project.wiki, title:
    //           version.wiki_page_title

    //           content = with_references config[:content], project
    //           WikiContent.create! page: page, author: User.admin.first, text:
    //           content

    //      version.save!
    auto wiki_page_title = config["title"].as<std::string>();

    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::WikiPages>
        mapper_wiki_pages(clientPtr);
    drogon_model::openproject6::WikiPages wiki_pages;
    // oh i dont know how to get wiki id!!
    // wiki_pages.setWikiId(); //integer NOT_NULL ;
    wiki_pages.setTitle(wiki_page_title);  // character_varying NOT_NULL ;
    wiki_pages.setCreatedOn(
        trantor::Date::now());       // timestamp_without_time_zone NOT_NULL ;
    wiki_pages.setProtected(false);  // boolean DEFAULT=false NOT_NULL;
    // wiki_pages.setParentId(); //integer  ;
    wiki_pages.setSlug("");  // character_varying NOT_NULL ;
    wiki_pages.setUpdatedAt(
        trantor::Date::now());  // timestamp_without_time_zone NOT_NULL ;

    mapper_wiki_pages.insert(wiki_pages);
  }
};
}  // namespace DemoData
}  // namespace seeder
}  // namespace openproj
