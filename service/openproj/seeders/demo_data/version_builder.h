#pragma once
#include <drogon/drogon.h>
#include <yaml-cpp/yaml.h>
#include "models/Versions.h"
#include "models/WikiPages.h"
#include "models/Wikis.h"
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
    // versions.setStartDate(trantor::Date::now());  // date  ;
    if (config["wiki"]) {
      auto wiki_page_title = config["wiki"]["title"].as<std::string>();
      versions.setWikiPageTitle(wiki_page_title);
    }
    mapper_versions.insert(versions);
    auto version_id = *versions.getId().get();
    if (config["wiki"]) {
      set_wiki(version_id, config["wiki"]);
    }
    return version_id;
  }

  void set_wiki(int version_id, YAML::Node wiki_config) {
    /*
  version.wiki_page_title = config[:title]
  page = WikiPage.create! wiki: version.project.wiki, title:
  version.wiki_page_title

  content = with_references config[:content], project
  WikiContent.create! page: page, author: User.admin.first, text: content

  version.save!
*/

    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::Wikis> mapper_wikis(
        clientPtr);
    drogon_model::openproject6::Wikis wikis;
    wikis.setProjectId(this->project_id);  // integer NOT_NULL ;
    wikis.setStartPage("Wiki");            // character_varying NOT_NULL ;
    wikis.setStatus(1);                    // integer DEFAULT=1 NOT_NULL;
    wikis.setCreatedAt(
        trantor::Date::now());  // timestamp_without_time_zone NOT_NULL ;
    wikis.setUpdatedAt(
        trantor::Date::now());  // timestamp_without_time_zone NOT_NULL ;
    mapper_wikis.insert(wikis);
    auto wiki_id = *wikis.getId().get();

    auto wiki_page_title = wiki_config["title"].as<std::string>();

    drogon::orm::Mapper<drogon_model::openproject6::WikiPages>
        mapper_wiki_pages(clientPtr);
    drogon_model::openproject6::WikiPages wiki_pages;
    wiki_pages.setWikiId(wiki_id);
    wiki_pages.setTitle(wiki_page_title);
    wiki_pages.setCreatedOn(trantor::Date::now());
    wiki_pages.setProtected(false);  // DEFAULT=false NOT_NULL;
    // wiki_pages.setParentId(); // Todo ;
    wiki_pages.setSlug(wiki_page_title);  // Todo
    wiki_pages.setUpdatedAt(trantor::Date::now());

    mapper_wiki_pages.insert(wiki_pages);
  }
};
}  // namespace DemoData
}  // namespace seeder
}  // namespace openproj
