#pragma once
#include "../../services/scm/base_repository_service.h"
//
// Implements the creation of a local repository.
namespace openproj {
namespace service {
namespace Scm{
class CreateManagedRepositoryService : public BaseRepositoryService {
public:
  //
  // Checks if a given repository may be created and managed locally.
  // Registers an job to create the repository on disk.
  //
  // @return True if the repository creation request has been initiated, false otherwise.
//   void call() {
//    if ( repository.managed? && repository.manageable?) {

//      //
//      // We want to move this functionality in a Delayed Job,
//      // but this heavily interferes with the error handling of the whole
//      // repository management process.
//      // Instead, this will be refactored into a single service wrapper for
//      // creating and deleting repositories, which provides transactional DB access
//      // as well as filesystem access.
//      if ( repository.class.manages_remote?) {
//        Scm::CreateRemoteRepositoryJob.new(repository, perform_now: true).perform
//      else
//        Scm::CreateLocalRepositoryJob.new(repository).perform
//      }
//      return true
//    }

//    false
//  rescue Errno::EACCES
//    this->rejected = I18n.t("repositories.errors.path_permission_failed",
//                       path: repository.root_url)
//    false
//  rescue SystemCallError => e
//    this->rejected = I18n.t("repositories.errors.filesystem_access_failed",
//                       message: e.message)
//    false
//  rescue OpenProject::Scm::Exceptions::ScmError => e
//    this->rejected = e.message
//    false
//  }

  //
  // Returns the error symbol
//   void localized_rejected_reason() {
//    this->rejected ||= I18n.t("repositories.errors.not_manageable")
//  }
};
}
}
}
