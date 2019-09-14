#include "./list_optional.h"

namespace Queries::Filters::Shared {
  namespace CustomFields {
    class User : public ListOptional {
      //
      // User CFs may reference the 'me' value, so use the values helpers
      // from the Me mixin, which will override the ListOptional value_objects definition.
      // include ::Queries::WorkPackages::Filter::MeValueFilterMixin

       void allowed_values() {
        @allowed_values ||= begin
          me_allowed_value + super
        }
      }
    }
  }
}
