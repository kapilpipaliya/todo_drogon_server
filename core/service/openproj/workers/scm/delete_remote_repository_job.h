//
// Provides an asynchronous job to delete a managed repository on the filesystem.
// Currently, this is run synchronously due to potential issues
// with error handling.
// We envision a repository management wrapper that covers transactional
// creation and deletion of repositories BOTH on the database and filesystem.
// Until then, a synchronous process is more failsafe.
namespace openproject {
class Scm::DeleteRemoteRepositoryJob : public Scm::RemoteRepositoryJob {
   void perform() {
    send_request(repository_request.merge(action: :delete))
  }
}
