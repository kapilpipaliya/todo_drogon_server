namespace OAuth {
  class CleanupJob : public ::RakeJob {
     CleanupJob() {
      super 'doorkeeper:db:cleanup'
    }
  }
}
