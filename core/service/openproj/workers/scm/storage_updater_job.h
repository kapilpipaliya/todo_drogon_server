#pragma once
#include "../application_job.h"
#include "caf/all.hpp"
namespace openproj {
namespace worker {
namespace Scm {
class StorageUpdaterJob : public caf::event_based_actor, public ApplicationJob {
 public:
  //   StorageUpdaterJob(repository) {
  //    this->id = repository.id

  //    unless repository.scm.storage_available?
  //      raise OpenProject::Scm::Exceptions::ScmError.new(
  //        I18n.t("repositories.storage.not_available")
  //      )
  //    }
  //  }

  void perform() {
    //    repository = Repository.find this->id
    //    bytes = repository.scm.count_repository!

    //    repository.update_attributes!(
    //      required_storage_bytes: bytes,
    //      storage_updated_at: Time.now,
    //    )
    //  rescue ActiveRecord::RecordNotFound
    //    Rails.logger.warn("StorageUpdater requested for Repository
    //    ##{this->id}, which could not be found.")
  }

  //
  // We don"t want to repeat failing jobs here,
  // as they might have failed due to I/O problems and thus,
  // we rather keep the old outdated value until an event
  // triggers the update again.
  int max_attempts() { return 1; }
};
}  // namespace Scm
}  // namespace openproj
}
