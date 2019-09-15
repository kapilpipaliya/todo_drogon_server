#pragma once
#include "../application_job.h"
//
// Provides an asynchronous job to delete a managed repository on the filesystem.
// Currently, this is run synchronously due to potential issues
// with error handling.
// We envision a repository management wrapper that covers transactional
// creation and deletion of repositories BOTH on the database and filesystem.
// Until then, a synchronous process is more failsafe.
namespace openproject {
namespace Scm {

class DeleteLocalRepositoryJob : public ApplicationJob {
public:
//   DeleteLocalRepositoryJob(managed_path) {
//    this->managed_path = managed_path
//  }

   void perform() {
    // Delete the repository project itself.
//    FileUtils.remove_dir(this->managed_path)
  }

   bool destroy_failed_jobs() {
    return true;
  }
};
}
}
