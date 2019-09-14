#include "./base.h"

namespace Queries::Filters::Shared {
  namespace CustomFields {
    class ListOptional : public Base {
       void value_objects() {
        case custom_field.field_format
        when 'version'
          ::Version.where(id: values)
        when 'list'
          custom_field.custom_options.where(id: values)
        else
          super
        }
      }

       void ar_object_filter?() {
        true
      }

       void type() {
        :list_optional
      }

      protected:

       void type_strategy_class() {
        ::Queries::Filters::Strategies::CfListOptional
      }
    }
  }
}
