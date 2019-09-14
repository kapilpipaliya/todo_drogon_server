//
// Provides an asynchronous job to delete a managed repository on the filesystem.
// Currently, this is run synchronously due to potential issues
// with error handling.
// We envision a repository management wrapper that covers transactional
// creation and deletion of repositories BOTH on the database and filesystem.
// Until then, a synchronous process is more failsafe.
class Scm::DeleteLocalRepositoryJob : public ApplicationJob {
   DeleteLocalRepositoryJob(managed_path) {
    this->managed_path = managed_path
  }

   void perform() {
    // Delete the repository project itself.
    FileUtils.remove_dir(this->managed_path)
  }

   void destroy_failed_jobs?() {
    true
  }
}
