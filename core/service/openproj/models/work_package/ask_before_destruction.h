#pragma once
namespace openproj {
namespace WorkPackageN::AskBeforeDestruction {
  // extend ActiveSupport::Concern

//  DestructionRegistration = Struct.new(:klass, :check, :action)

//   void included(base) {
//    base.extend(ClassMethods)

//    base.class_attribute :registered_associated_to_ask_before_destruction
//  }

  namespace ClassMethods {
//     void cleanup_action_required_before_destructing?(work_packages) {
//      !associated_to_ask_before_destruction_of(work_packages).empty?
//    }

//     void cleanup_associated_before_destructing_if_required(work_packages, user, to_do = { action: 'destroy' }) {
//      cleanup_required = cleanup_action_required_before_destructing?(work_packages)

//      (!cleanup_required ||
//       (cleanup_required &&
//        cleanup_each_associated_class(work_packages, user, to_do)))
//    }

//     void associated_classes_to_address_before_destruction_of(work_packages) {
//      associated = []

//      registered_associated_to_ask_before_destruction.each { |registration|
//        if ( registration.check.call(work_packages)) { associated << registration.klass ;}
//      }

//      associated
//    }

//    private:

//     void associated_to_ask_before_destruction_of(work_packages) {
//      associated = {}

//      registered_associated_to_ask_before_destruction.each { |registration|
//        if ( registration.check.call(work_packages)) { associated[registration.klass] = registration.action ;}
//      }

//      associated
//    }

//     void associated_to_ask_before_destruction(klass, check, action) {
//      this->registered_associated_to_ask_before_destruction ||= []

//      registration = DestructionRegistration.new(klass, check, action)

//      this->registered_associated_to_ask_before_destruction << registration
//    }

//     void cleanup_each_associated_class(work_packages, user, to_do) {
//      ret = false

//      transaction {
//        associated_to_ask_before_destruction_of(work_packages).each { |_klass, method|
//          ret = method.call(work_packages, user, to_do)
//        }

//        raise ActiveRecord::Rollback unless ret
//      }

//      ret
//    }
  }
}
}
