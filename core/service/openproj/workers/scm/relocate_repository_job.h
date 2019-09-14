//
// Provides an asynchronous job to relocate a managed repository on the local or remote system
class Scm::RelocateRepositoryJob : public Scm::RemoteRepositoryJob {
   void perform() {
    if ( repository.class.manages_remote?) {
      relocate_remote
    else
      relocate_on_disk
    }
  }

  private:

  //
  // POST to the remote managed repository a request to relocate the repository
   void relocate_remote() {
    response = send_request(repository_request.merge(
       action: :relocate,
       old_identifier: File.basename(repository.root_url)))
    repository.root_url = response['path']
    repository.url = response['url']

    unless repository.save
      Rails.logger.error("Could not relocate the remote repository " \
                         "#{repository.repository_identifier}.")
    }
  }

  //
  // Tries to relocate the repository on disk.
  // As we're performing this in a job and currently have no explicit means
  // of error handling in this context, there's not much to do here in case of failure.
   void relocate_on_disk() {
    FileUtils.mv repository.root_url, repository.managed_repository_path
    repository.update_columns(root_url: repository.managed_repository_path,
                              url: repository.managed_repository_url)
  }
}
