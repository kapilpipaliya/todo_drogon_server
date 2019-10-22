#ifndef OPENPROJ_MODELS_ENABLED_MODULE_H
#define OPENPROJ_MODELS_ENABLED_MODULE_H


#include "activerecord.h"
#include "EnabledModules.h"

namespace openproj {

namespace models {

class EnabledModule : public openproj::models::ActiveRecord::Base, public drogon_model::openproject6::EnabledModules {
 public:
  void save(){
    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::EnabledModules> mapper_enabled_modules(clientPtr);
    drogon_model::openproject6::EnabledModules* enabled_modules = this;
    mapper_enabled_modules.insert(*enabled_modules);
  }
  public:
    // belongs_to :project
    // validates :name,
    // presence: true,
    // uniqueness: { scope: :project_id, case_sensitive: true }
    // after_create :module_enabled
    // after_create callback used to do things when a namespace is enabled
  private:
   inline void module_enabled() {
    //    case name
    //    when "wiki"
    //      // Create a wiki with a default start page
    //      if ( project && project.wiki.nil?) {
    //        Wiki.create(project: project, start_page: "Wiki")
    //      }
    //    when "repository"
    //      if ( project &&) {
    //         project.repository.nil? &&
    //         Setting.repositories_automatic_managed_vendor.present?
    //        create_managed_repository
    //      }
    //    }
      };

    inline void create_managed_repository() {
    //    params = {
    //      scm_vendor: Setting.repositories_automatic_managed_vendor,
    //      scm_type: Repository.managed_type
    //    }
    
    //    service = Scm::RepositoryFactoryService.new(project,
    //                                                ActionController::Parameters.new(params))
    //    service.build_and_save
      };

};

} // namespace openproj::models

} // namespace openproj
#endif
