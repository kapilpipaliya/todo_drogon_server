#pragma once
namespace openproj {
namespace models {
namespace Concerns {
  namespace VirtualAttribute {
    // extend ActiveSupport::Concern

//    class_methods {
//       void virtual_attribute(attribute, cast_type: :string, &block) {
//        attribute attribute, cast_type
//        define_attribute_method attribute

//        // include InstanceMethods

//        _define_virtual_attribute_setter(attribute)
//        _define_virtual_attribute_getter(attribute, &block)
//        _define_virtual_attribute_reload(attribute)
//        _define_virtual_attributes_hook(attribute)
//      }

//      private:

//       void _define_virtual_attributes_hook(attribute) {
//        define_method :attributes { |*args|
//          // Ensure attribute has been read
//          send(attribute)
//          super(*args)
//        }

//        // Ensure the virtual attribute is unset before destroying
//        before_destroy { send(:"#{attribute}=", nil) }
//      }

//       void _define_virtual_attribute_setter(attribute) {
//        define_method "#{attribute}=" { |value|
//          set_virtual_attribute(attribute, value) if ( send(attribute) != value) {
//          instance_variable_set(:"this->#{attribute}_set", true)
//          instance_variable_set(:"this->#{attribute}", value)
//        }
//      }

//       void _define_virtual_attribute_getter(attribute, &block) {
//        define_method attribute {
//          if ( instance_variable_get(:"this->#{attribute}_set")) {
//            instance_variable_get(:"this->#{attribute}")
//          else
//            value = instance_eval(&block)

//            set_virtual_attribute_was(attribute, value)

//            instance_variable_set(:"this->#{attribute}", value)
//          }
//        }
//      }

//       void _define_virtual_attribute_reload(attribute) {
//        define_method :reload { |*args|
//          instance_variable_set(:"this->#{attribute}", nil)
//          instance_variable_set(:"this->#{attribute}_set", nil)

//          super(*args)
//        }
//      }
//    }

//    namespace InstanceMethods {
//      // Used to persists the changes to the virtual attribute in the mutation_tracker used by
//      // AR::Dirty so that it looks like every other attribute.
//      // Using attribute_will_change! does not place the value in the tracker but merely forces
//      // the attribute to be returned when asking the object for changes.
//       void set_virtual_attribute_was(attribute, value) {
//        attributes = mutations_from_database.send(:attributes)
//        attributes[attribute.to_s].instance_variable_set(:this->value_before_type_cast, value)
//      }

//       void set_virtual_attribute(attribute, value) {
//        attributes = mutations_from_database.send(:attributes)
//        attributes[attribute.to_s] = attributes[attribute.to_s].with_value_from_user(value)
//      }
//    }
//  }
}
}
}
}