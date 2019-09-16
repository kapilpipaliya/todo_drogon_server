#pragma once
namespace openproj {
namespace service {
class ServiceResult{
  // attr_accessor :success,
//                :errors,
//                :result,
//                :message,
//                :message_type,
//                :context,
//                :dependent_results

//   ServiceResult(success: false,
//                 errors: nil,
//                 message: nil,
//                 message_type: nil,
//                 context: {},
//                 dependent_results: [],
//                 result: nil)
//    this->success = success
//    this->result = result
//    this->context = context
//    this->dependent_results = dependent_results

//    initialize_errors(errors)
//    initialize_message(message)
//  }

//  alias success? :success

   bool failure() {
//    !success?
  }

//   void merge!(other) {
//    merge_success!(other)
//    merge_dependent!(other)
//  }

  //
  // Print messages to flash
//   void apply_flash_message!(flash) {
//    type = get_message_type

//    if ( message && type) {
//      flash[type] = message
//    }
//  }

   void all_results() {
//    dependent_results.map(&:result).tap { |results|
//      results.unshift result unless result.nil?
//    }
  }

   void all_errors() {
//    [errors] + dependent_results.map(&:errors)
  }

  //
  // Collect all present errors for the given result
  // and dependent results.
  //
  // Returns a map of the service reuslt to the error object
//   void results_with_errors(include_self: true) {
//    results =
//      if ( include_self) {
//        [self] + dependent_results
//      else
//        dependent_results
//      }

//    results.reject { |call| call.errors.empty? }
//  }


   void self_and_dependent() {
//    [self] + dependent_results
  }

//   void add_dependent!(dependent) {
//    merge_success!(dependent)

//    inner_results = dependent.dependent_results
//    dependent.dependent_results = []

//    dependent_results << dependent
//    this->dependent_results += inner_results
//  }

   void on_success() {
//    if ( success?) { yield(self) ;}
  }

   void on_failure() {
//    if ( failure?) { yield(self) ;}
  }

  private:

//   void initialize_errors(errors) {
//    this->errors =
//      if ( errors) {
//        errors
//      } else if ( result.respond_to?(:errors)) {
//        result.errors
//      else
//        ActiveModel::Errors.new(self)
//      }
//  }

//   void initialize_message(message) {
//    this->message =
//      if ( message) {
//        message
//      } else if ( failure? && errors.is_a?(ActiveModel::Errors)) {
//        errors.full_messages.join("")
//      }
//  }

//   void get_message_type() {
//    if ( message_type.present?) {
//      message_type.to_sym
//    } else if ( success?) {
//      :notice
//    else
//      :error
//    }
//  }

//   void merge_success!(other) {
//    this->success &&= other.success
//  }

//   void merge_dependent!(other) {
//    this->dependent_results += other.dependent_results
//  }
};
}
}
