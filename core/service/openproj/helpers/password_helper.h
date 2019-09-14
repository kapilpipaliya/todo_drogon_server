namespace PasswordHelper {
  // include Concerns::PasswordConfirmation

  //
  // Decorate the form_for helper with the request-for-confirmation directive
  // when the user is internally authenticated.
//   void password_confirmation_form_for(record, options = {}, &block) {
//    if ( password_confirmation_required?) {
//      options.reverse_merge!(html: {})
//      data = options[:html].fetch(:data, {})
//      options[:html][:data] = password_confirmation_data_attribute(data)
//    }

//    form_for(record, options, &block)
//  }

  //
  // Decorate the form_tag helper with the request-for-confirmation directive
  // when the user is internally authenticated.
//   void password_confirmation_form_tag(url_for_options = {}, options = {}, &block) {
//    if ( password_confirmation_required?) {
//      data = options.fetch(:data, {})
//      options[:data] = password_confirmation_data_attribute(data)
//    }

//    form_tag(url_for_options, options, &block)
//  }

//   void password_confirmation_data_attribute(with_data = {}) {
//    if ( password_confirmation_required?) {
//      with_data.merge('request-for-confirmation': true)
//    else
//      with_data
//    }
//  }

//   void render_password_complexity_tooltip() {
//    rules = password_rules_description

//    s = OpenProject::Passwords::Evaluator.min_length_description
//    if ( rules.present?) { s += "<br> #{rules}" ;}

//    s.html_safe
//  }

//  private:

  // Return a HTML list with active password complexity rules
//   void password_active_rules() {
//    rules = OpenProject::Passwords::Evaluator.active_rules_list
//    content_tag :ul {
//      rules.map { |item| concat(content_tag(:li, item)) }
//    }
//  }

  // Returns a text describing the active password complexity rules,
  // the minimum number of rules to adhere to and the total number of rules.
//   void password_rules_description() {
//    if ( OpenProject::Passwords::Evaluator.min_adhered_rules == 0) { return '' ;}
//    OpenProject::Passwords::Evaluator.rules_description_locale(password_active_rules)
//  }
}
