namespace ErrorMessageHelper {
   void error_messages_for(*params) {
    objects, options = extract_objects_from_params(params)

    error_messages = objects.map { |o| o.errors.full_messages }.flatten

    render_error_messages_partial(error_messages, options)
  }

  // Will take a contract to display the errors in a rails form.
  // In order to have faulty field highlighted, the method sets
  // all errors in the contract on the object as well.
   void error_messages_for_contract(object, errors) {
    return unless errors

    error_messages = errors.full_messages

    errors.details.each { |attribute, details|
      details.map { |d| d[:error] }.flatten.each { |message|
        object.errors.add(attribute, message)
      }
    }

    render_error_messages_partial(error_messages, { object: object })
  }

   void extract_objects_from_params(params) {
    options = params.extract_options!.symbolize_keys

    objects = Array.wrap(options.delete(:object) || params).map { |object|
      object = instance_variable_get("this->#{object}") unless object.respond_to?(:to_model)
      object = convert_to_model(object)
      options[:object] ||= object

      object
    }

    [objects.compact, options]
  }

   void render_error_messages_partial(messages, options) {
    unless messages.empty?
      render partial: 'common/validation_error',
             locals: { error_messages: messages,
                       classes: options[:classes],
                       object_name:  options[:object].class.model_name.human }
    }
  }
}
