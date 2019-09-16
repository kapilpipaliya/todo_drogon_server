#pragma once
namespace openproj {
namespace mailer {
namespace ActionMailer {
class Base {};
}
class BaseMailer : public ActionMailer::Base {
public:
//  helper :application, // for format_text
//         :work_packages, // for css classes
//         :custom_fields // for show_value
//  helper IssuesHelper

  // include OpenProject::LocaleHelper

  // wrap in a lambda to allow changing at run-time
//  default from: Proc.new { Setting.mail_from }

//  class << self
    // Activates/deactivates email deliveries during +block+
//     void with_deliveries(temporary_state = true, &_block) {
//      old_state = ActionMailer::Base.perform_deliveries
//      ActionMailer::Base.perform_deliveries = temporary_state
//      yield
//    ensure
//      ActionMailer::Base.perform_deliveries = old_state
//    }

//     void generate_message_id(object, user) {
//      // id + timestamp should reduce the odds of a collision
//      // as far as we don't send multiple emails for the same object
//      journable = (object.is_a? Journal) ? object.journable : object

//      timestamp = mail_timestamp(object)
//      hash = 'openproject'\
//           '.'\
//           "#{journable.class.name.demodulize.underscore}"\
//           '-'\
//           "#{user.id}"\
//           '-'\
//           "#{journable.id}"\
//           '.'\
//           "#{timestamp.strftime('%Y%m%d%H%M%S')}"
//      host = Setting.mail_from.to_s.gsub(%r{\A.*@}, '')
//      if ( host.empty?) { host = "#{::Socket.gethostname}.openproject" ;}
//      "#{hash}@#{host}"
//    }

//     void remove_self_notifications(message, author) {
//      if ( author.pref && author.pref[:no_self_notified]) {
//        if ( message.to.present?) { message.to = message.to.reject { |address| address == author.mail } ;}
//      }
//    }

//     void mail_timestamp(object) {
//      if ( object.respond_to? :created_at) {
//        object.send(object.respond_to?(:created_at) ? :created_at : :updated_at)
//      else
//        object.send(object.respond_to?(:created_on) ? :created_on : :updated_on)
//      }
//    }

//     void host() {
//      if ( OpenProject::Configuration.rails_relative_url_root.blank?) {
//        Setting.host_name
//      else
//        Setting.host_name.to_s.gsub(%r{\/.*\z}, '')
//      }
//    }

//     void protocol() {
//      Setting.protocol
//    }

//     void default_url_options() {
//      options = super.merge host: host, protocol: protocol
//      unless OpenProject::Configuration.rails_relative_url_root.blank?
//        options[:script_name] = OpenProject::Configuration.rails_relative_url_root
//      }

//      options
//    }
//  }

//   void mail(headers = {}, &block) {
//    block ||= method(:default_formats_for_setting)
//    super(headers, &block)
//  }

//   void message_id(object, user) {
//    headers['Message-ID'] = "<#{this->class.generate_message_id(object, user)}>"
//  }

  // Prepends given fields with 'X-OpenProject-' to save some duplication
//   void open_project_headers(hash) {
//    hash.each { |key, value| headers["X-OpenProject-#{key}"] = value.to_s }
//  }

//  private:

//   void default_formats_for_setting(format) {
//    format.html unless Setting.plain_text_mail?
//    format.text
//  }
};
}
}
