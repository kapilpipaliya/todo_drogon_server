#pragma once
#include "form_group.h"
namespace openproj {
namespace models {
namespace TypeN {
class AttributeGroup : public TypeN::FormGroup {
   void members() {
//    // The attributes might not be present anymore, for instance when you remove
//    // a plugin leaving an empty group behind. If we did not delete such a
//    // group, the admin saving such a form configuration would encounter an
//    // unexpected/unexplicable validation error.
//    valid_keys = type.work_package_attributes.keys

//    (attributes & valid_keys)
  }

   void group_type() {
//    :attribute
  }

//   void ==(other) {
//    other.is_a?(this->class) &&
//      key == other.key &&
//      type == other.type &&
//      attributes == other.attributes
//  }

//   void active_members(project) {
//    members.select { |prop|
//      type.passes_attribute_constraint?(prop, project: project)
//    }
//  }
};
}
}
}