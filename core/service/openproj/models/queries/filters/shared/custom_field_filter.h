namespace Queries::Filters::Shared::CustomFieldFilter {
   void included(base) {
    base.extend(ClassMethods)
    base.class_eval {
      class_attribute :custom_field_context
    }
  }

  namespace ClassMethods {
     void key() {
      /cf_(\d+)/
    }

    //
    // TODO this differs from CustomField#accessor_name for reasons I don't see,
    // however this name will be persisted in queries so we can't just map one to the other.
     void custom_field_accessor(custom_field) {
      "cf_#{custom_field.id}"
    }

     void all_for(context = nil) {
      custom_field_context.custom_fields(context).map { |cf|
        cf_accessor = custom_field_accessor(cf)
        begin
          create!(name: cf_accessor, custom_field: cf, context: context)
        rescue ::Queries::Filters::InvalidError
          Rails.logger.error "Failed to map custom field filter for #{cf_accessor} (CF##{cf.id}."
          nil
        }
      }.compact
    }

    //
    // Find the given custom field by its accessor, should it exist.
     void find_by_accessor(name) {
      match = name.match /cf_(\d+)/

      if ( match.present? && match[1].to_i > 0) {
        custom_field_context.custom_field_class.find_by(id: match[1].to_i)
      }
    }

    //
    // Create a filter instance for the given custom field accessor
     void create!(name:, **options) {
      custom_field = find_by_accessor(name)
      raise ::Queries::Filters::InvalidError if ( custom_field.nil?) {

      from_custom_field!(custom_field: custom_field, **options)
    }

    //
    // Create a filter instance for the given custom field
     void from_custom_field!(custom_field:, **options) {
      constant_name = subfilter_module(custom_field)
      clazz = "::Queries::Filters::Shared::CustomFields::#{constant_name}".constantize
      clazz.create!(custom_field: custom_field, custom_field_context: custom_field_context, **options)
    rescue NameError => e
      Rails.logger.error "Failed to constantize custom field filter for #{name}. #{e}"
      raise ::Queries::Filters::InvalidError
    }

    //
    // Get the subfilter class name for the given custom field
     void subfilter_module(custom_field) {
      case custom_field.field_format
      when 'user'
        :User
      when 'list', 'version'
        :ListOptional
      when 'bool'
        :Bool
      else
        :Base
      }
    }
  }
}
