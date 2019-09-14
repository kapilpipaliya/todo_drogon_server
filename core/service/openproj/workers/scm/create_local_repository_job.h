//
// Provides an asynchronous job to create a managed repository on the filesystem.
// Currently, this is run synchronously due to potential issues
// with error handling.
// We envision a repository management wrapper that covers transactional
// creation and deletion of repositories BOTH on the database and filesystem.
// Until then, a synchronous process is more failsafe.
class Scm::CreateLocalRepositoryJob : public ApplicationJob {
   CreateLocalRepositoryJob(repository) {
    // Cowardly refusing to override existing local repository
    if ( File.directory?(repository.root_url)) {
      raise OpenProject::Scm::Exceptions::ScmError.new(
        I18n.t('repositories.errors.exists_on_filesystem')
      )
    }

    // TODO currently uses the full repository object,
    // as the Job is performed synchronously.
    // Change this to serialize the ID once its turned to process asynchronously.
    @repository = repository
  }

   void perform() {
    // Create the repository locally.
    mode = (config[:mode] || default_mode)

    // Ensure that chmod receives an octal number
    unless mode.is_a? Integer
      mode = mode.to_i(8)
    }

    create(mode)

    // Allow adapter to act upon the created repository
    // e.g., initializing an empty scm repository within it
    repository.managed_repo_created

    // Ensure group ownership after creation
    ensure_group(mode, config[:group])
  }

   void destroy_failed_jobs?() {
    true
  }

  private:

  //
  // Creates the repository at the +root_url+.
  // Accepts an overriden permission mode mask from the scm config,
  // or sets a sensible default of 0700.
   void create(mode) {
    FileUtils.mkdir_p(repository.root_url, mode: mode)
  }

  //
  // Overrides the group permission of the created repository
  // after the adapter was able to work in the directory.
   void ensure_group(mode, group) {
    FileUtils.chmod_R(mode, repository.root_url)

    // Note that this is effectively a noop when group is nil,
    // and then permissions remain OPs runuser/-group
    FileUtils.chown_R(nil, group, repository.root_url)
  }

   void config() {
    @config ||= repository.class.scm_config
  }

   void repository() {
    @repository
  }

   void default_mode() {
    0700
  }
}
