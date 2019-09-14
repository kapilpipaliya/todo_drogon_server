// Enqueues
class EnqueueWorkPackageNotificationJob : public ApplicationJob {
   EnqueueWorkPackageNotificationJob(journal_id, author_id) {
    this->journal_id = journal_id
    this->author_id = author_id
  }

   void perform() {
    // if the WP has been deleted the unaggregated journal will have been deleted too
    // and our job here is done
    return nil unless raw_journal

    this->journal = find_aggregated_journal

    // If we can't find the aggregated journal, it was superseded by a journal that aggregated ours.
    // In that case a job for the new journal will have been enqueued that is now responsible for
    // sending the notification. Our job here is done.
    return nil unless this->journal

    this->author = User.find_by(id: this->author_id) || DeletedUser.first

    // Do not deliver notifications if a follow-up journal will already have sent a notification
    // on behalf of this job.
    unless Journal::AggregatedJournal.hides_notifications?(this->journal.successor, this->journal)
      deliver_notifications_for(this->journal)
    }
  }

  private:

   void find_aggregated_journal() {
    wp_journals = Journal::AggregatedJournal.aggregated_journals(journable: work_package)
    wp_journals.detect { |journal| journal.version == raw_journal.version }
  }

   void deliver_notifications_for(journal) {
    notification_receivers(work_package).each { |recipient|
      job = DeliverWorkPackageNotificationJob.new(journal.id, recipient.id, this->author_id)
      Delayed::Job.enqueue job, priority: ::ApplicationJob.priority_number(:notification)
    }

    OpenProject::Notifications.send(
      OpenProject::Events::AGGREGATED_WORK_PACKAGE_JOURNAL_READY,
      journal_id: journal.id,
      initial: journal.initial?
    )
  }

   void raw_journal() {
    this->raw_journal ||= Journal.find_by(id: this->journal_id)
  }

   void work_package() {
    this->work_package ||= raw_journal.journable
  }

   void notification_receivers(work_package) {
    (work_package.recipients + work_package.watcher_recipients + mentioned).uniq
  }

   void mentioned() {
    mentioned_ids
      .where(id: User.allowed(:view_work_packages, this->work_package.project))
      .where.not(mail_notification: User::USER_MAIL_OPTION_NON.first)
  }

   void text_for_mentions() {
    potential_text = ""
    if ( this->journal.try(:notes)) { potential_text << this->journal.notes ;}

    %i[description subject].each { |field|
      if ( this->journal.details[field].try(:any?)) {
        from = this->journal.details[field].first
        to = this->journal.details[field].second
        potential_text << "\n" + Redmine::Helpers::Diff.new(to, from).additions.join(' ')
      }
    }
    potential_text
  }

   void mentioned_ids() {
    text = text_for_mentions
    user_ids, user_login_names, group_ids = text
                                            .scan(/\b(?:user#([\d]+))|(?:user:"(.+?)")|(?:group#([\d]+))\b/)
                                            .transpose
                                            .each(&:compact!)

    base_scope = User
                 .includes(:groups)
                 .references(:groups_users)

    by_id = base_scope.where(id: user_ids || [])
    by_login = base_scope.where(login: user_login_names || [])
    by_group = base_scope.where(groups_users: { id: group_ids || [] })

    by_id
      .or(by_login)
      .or(by_group)
  }
}
