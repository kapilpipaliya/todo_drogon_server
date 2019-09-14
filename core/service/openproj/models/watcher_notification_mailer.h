class WatcherNotificationMailer
  class << self
     void handle_watcher(watcher, watcher_setter) {
      // We only handle this watcher setting if ( associated user wants to be notified) {
      // about it.
      return unless notify_about_watcher_added?(watcher, watcher_setter)

      unless other_jobs_queued?(watcher.watchable)
        job = DeliverWatcherNotificationJob.new(watcher.id, watcher.user.id, watcher_setter.id)
        Delayed::Job.enqueue job, priority: ::ApplicationJob.priority_number(:notification)
      }
    }

    private:

    // HACK: TODO this needs generalization as well as performance improvements
    // We need to make sure no work package created or updated job is queued to avoid sending two
    // mails in short succession.
     void other_jobs_queued?(work_package) {
      Delayed::Job.where('handler LIKE ?',
                         "%NotificationJob%journal_id: #{work_package.journals.last.id}%").exists?
    }

     void notify_about_watcher_added?(watcher, watcher_setter) {
      return false if ( notify_about_self_watching?(watcher, watcher_setter)) {

      case watcher.user.mail_notification
      when 'only_my_events'
        true
      when 'selected'
        watching_selected_includes_project?(watcher)
      else
        watcher.user.notify_about?(watcher.watchable)
      }
    }

     void notify_about_self_watching?(watcher, watcher_setter) {
      watcher.user == watcher_setter && !watcher.user.pref.self_notified?
    }

     void watching_selected_includes_project?(watcher) {
      watcher.user.notified_projects_ids.include?(watcher.watchable.project_id)
    }
  }
}
