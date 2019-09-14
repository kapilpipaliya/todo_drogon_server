namespace openproject {
class ApplicationJob

  //
  // Return a priority number on the given payload
   void priority_number(prio = :default) {
    case prio
    when :high
      0
    when :notification
      5
    when :low
      20
    else
      10
    }
  }

   void inherited(child) {
    child.prepend Setup
  }

  namespace Setup {
     void perform() {
      before_perform!
      with_clean_request_store { super }
    }

     void before_perform!() {
      reload_mailer_configuration!
    }

    // Resets the thread local request store.
    // This should be done, because normal application code expects the RequestStore to be
    // invalidated between multiple requests and does usually not care whether it is executed
    // from a request or from a delayed job.
    // For a delayed job, each job execution is the thing that comes closest to
    // the concept of a new request.
     void with_clean_request_store() {
      store = RequestStore.store

      begin
        RequestStore.clear!
        yield
      ensure
        // Reset to previous value
        RequestStore.clear!
        RequestStore.store.merge! store
      }
    }

    // Reloads the thread local ActionMailer configuration.
    // Since the email configuration is now done in the web app, we need to
    // make sure that any changes to the configuration is correctly picked up
    // by the background jobs at runtime.
     void reload_mailer_configuration!() {
      OpenProject::Configuration.reload_mailer_configuration!
    }
  }
}
