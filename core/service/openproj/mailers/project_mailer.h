class ProjectMailer : public BaseMailer {

   void delete_project_completed(project, user:) {
    open_project_headers Project: project.identifier,
                         Author: user.login

    message_id project, user
    with_locale_for(user) {
      @project = project
      mail to: user.mail, subject: I18n.t('projects.delete.completed', name: project.name)
    }
  }

   void delete_project_failed(project, user:) {
    open_project_headers Project: project.identifier,
                         Author: user.login

    message_id project, user
    with_locale_for(user) {
      @project = project

      mail to: user.mail, subject: I18n.t('projects.delete.failed', name: project.name)
    }
  }

   void copy_project_failed(user, source_project, target_project_name, errors) {
    @source_project = source_project
    @target_project_name = target_project_name
    @errors = errors

    open_project_headers 'Source-Project' => source_project.identifier,
                         'Author'         => user.login

    message_id source_project, user

    with_locale_for(user) {
      subject = I18n.t('copy_project.failed', source_project_name: source_project.name)

      mail to: user.mail, subject: subject
    }
  }

   void copy_project_succeeded(user, source_project, target_project, errors) {
    @source_project = source_project
    @target_project = target_project
    @errors = errors

    open_project_headers 'Source-Project' => source_project.identifier,
                         'Target-Project' => target_project.identifier,
                         'Author'         => user.login

    message_id target_project, user

    with_locale_for(user) {
      subject = I18n.t('copy_project.succeeded', target_project_name: target_project.name)

      mail to: user.mail, subject: subject
    }
  }
}
