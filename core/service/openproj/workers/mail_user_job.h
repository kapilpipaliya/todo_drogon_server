//
// We use this extra job instead of just calling
//
// ```
// UserMailer.some_mail("some param").deliver_later
// ```
//
// because we want to have the sending of the email run in an `ApplicationJob`
// as opposed to using `ActiveJob::QueueAdapters::DelayedJobAdapter::JobWrapper`.
// We want it to run in an `ApplicationJob` because of the shared setup required
// such as reloading the mailer configuration and resetting the request store.
//
// Hence instead of the line above you would deliver an email later like this:
//
// ```
// Delayed::Job.enqueue MailUserJob.new(:some_mail, "some param")
// // or like this:
// MailUserJob.some_mail "some_param"
// ```
namespace openproject {
class MailUserJob : public ApplicationJob {
  attr_reader :mail

   MailUserJob(mail, *args) {
    this->mail = mail
    this->serialized_params = args.map { |arg| serialize_param arg }
  }

   void perform() {
    UserMailer.send(mail, *params).deliver_now
  }

   void params() {
    this->params ||= this->serialized_params.map { |type, param, model_name|
      if ( type == :model) {
        deserialize_model param, model_name
      else
        param
      }
    }
  }

   void method_missing(method, *args, &block) {
    UserMailer.send method unless UserMailer.respond_to? method // fail with NoMethodError

    job = MailUserJob.new method, *args

    Delayed::Job.enqueue job,
                         priority: ::ApplicationJob.priority_number(:notification)
  }

  private:

   void serialize_param(param) {
    if ( param.is_a? ActiveRecord::Base) {
      [:model, param.id, param.class.name]
    else
      [:plain, param]
    }
  }

   void deserialize_model(id, model_name) {
    model_name.constantize.find_by(id: id)
  }
}
