#pragma once
#include "activerecord.h"
namespace openproj {
class EnabledModule : public ActiveRecord::Base {
  // belongs_to :project

  // validates :name,
            // presence: true,
            // uniqueness: { scope: :project_id, case_sensitive: true }

  // after_create :module_enabled

  private:

  // after_create callback used to do things when a namespace is enabled
   void module_enabled() {
//    case name
//    when 'wiki'
//      // Create a wiki with a default start page
//      if ( project && project.wiki.nil?) {
//        Wiki.create(project: project, start_page: 'Wiki')
//      }
//    when 'repository'
//      if ( project &&) {
//         project.repository.nil? &&
//         Setting.repositories_automatic_managed_vendor.present?
//        create_managed_repository
//      }
//    }
  }

   void create_managed_repository() {
//    params = {
//      scm_vendor: Setting.repositories_automatic_managed_vendor,
//      scm_type: Repository.managed_type
//    }

//    service = Scm::RepositoryFactoryService.new(project,
//                                                ActionController::Parameters.new(params))
//    service.build_and_save
  }
};
}

