class Scm::StorageUpdaterJob : public ApplicationJob {
   StorageUpdaterJob(repository) {
    this->id = repository.id

    unless repository.scm.storage_available?
      raise OpenProject::Scm::Exceptions::ScmError.new(
        I18n.t('repositories.storage.not_available')
      )
    }
  }

   void perform() {
    repository = Repository.find this->id
    bytes = repository.scm.count_repository!

    repository.update_attributes!(
      required_storage_bytes: bytes,
      storage_updated_at: Time.now,
    )
  rescue ActiveRecord::RecordNotFound
    Rails.logger.warn("StorageUpdater requested for Repository ##{this->id}, which could not be found.")
  }

  //
  // We don't want to repeat failing jobs here,
  // as they might have failed due to I/O problems and thus,
  // we rather keep the old outdated value until an event
  // triggers the update again.
   void max_attempts() {
    1
  }
}
