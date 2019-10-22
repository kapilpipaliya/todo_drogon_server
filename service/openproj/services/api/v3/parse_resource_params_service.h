#pragma once
namespace openproj {
namespace service {
namespace API {
  namespace V3 {
    class ParseResourceParamsService {
    public:
      // attr_accessor :model,
//                    :representer,
//                    :current_user

//       ParseResourceParamsService(user, model: nil, representer: nil) {
//        this->current_user = user
//        this->model = model

//        this->representer = if ( !representer && model) {
//                             "API::V3::#{model.to_s.pluralize}::#{model}Representer".constantize
//                           } else if ( representer) {
//                             representer
//                           else
//                             raise "Representer not defined"
//                           }
//      }

//       void call(request_body) {
//        parsed = if ( request_body) {
//                   parse_attributes(request_body)
//                 else
//                   {}
//                 }

//        ServiceResult.new(success: true,
//                          result: parsed)
//      }

      private:

//       void parse_attributes(request_body) {
//        representer
//          .create(struct, current_user: current_user)
//          .from_hash(request_body)
//          .to_h
//          .except(:available_custom_fields)
//      }

       void struct_() {
//        if ( model&.new.respond_to?(:available_custom_fields)) {
//          OpenStruct.new available_custom_fields: model.new.available_custom_fields
//        else
//          OpenStruct.new
//        }
      }
    };
  }
}
}
}
