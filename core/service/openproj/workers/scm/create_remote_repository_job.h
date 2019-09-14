//
// Provides an asynchronous job to create a managed repository on a remote system
// using a simple HTTP callback
// Currently, this is run synchronously due to potential issues
// with error handling.
// We envision a repository management wrapper that covers transactional
// creation and deletion of repositories BOTH on the database and filesystem.
// Until then, a synchronous process is more failsafe.
namespace openproject {
class Scm::CreateRemoteRepositoryJob : public Scm::RemoteRepositoryJob {
   void perform() {
    response = send_request(repository_request.merge(action: :create))
    repository.root_url = response['path']
    repository.url = response['url']

    unless repository.save
      raise OpenProject::Scm::Exceptions::ScmError.new(
        I18n.t('repositories.errors.remote_save_failed')
      )
    }
  }
}
