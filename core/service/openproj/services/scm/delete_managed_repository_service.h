#pragma once
#include "../../services/scm/base_repository_service.h"
//
// Implements the asynchronous deletion of a local repository.
namespace openproj {
namespace service {
namespace Scm {
class DeleteManagedRepositoryService : public Scm::BaseRepositoryService {
public:
  //
  // Checks if a given repository may be deleted
  // Registers an asynchronous job to delete the repository on disk.
  //
   void call() {
//    return false unless repository.managed?

//    if ( repository.class.manages_remote?) {
//      Scm::DeleteRemoteRepositoryJob.new(repository, perform_now: true).perform
//      true
//    else
//      delete_local_repository
//    }
//  rescue OpenProject::Scm::Exceptions::ScmError => e
//    this->rejected = e.message
//    false
  }

   void delete_local_repository() {
//    // Create necessary changes to repository to mark
//    // it as managed by OP, but delete asynchronously.
//    managed_path = repository.root_url

//    if ( File.directory?(managed_path)) {
//      //
//      // We want to move this functionality in a Delayed Job,
//      // but this heavily interferes with the error handling of the whole
//      // repository management process.
//      // Instead, this will be refactored into a single service wrapper for
//      // creating and deleting repositories, which provides transactional DB access
//      // as well as filesystem access.
//      Scm::DeleteLocalRepositoryJob.new(managed_path).perform
//    }

//    true
//  rescue SystemCallError => e
//    this->rejected = I18n.t('repositories.errors.managed_delete_local',
//                       path: repository.root_url,
//                       error_message: e.message)
//    false
  }

  //
  // Returns the error symbol
   void localized_rejected_reason() {
//    this->rejected ||= I18n.t('repositories.errors.managed_delete')
  }
};
}
}
}
