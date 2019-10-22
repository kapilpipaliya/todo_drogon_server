#pragma once
#include "../../services/base_services/delete.h"
namespace openproj {
namespace service {
namespace WorkPackages{
class DeleteService : public BaseServices::Delete_ {
public:
  // include ::WorkPackages::Shared::UpdateAncestors

   void call() {
//    in_context(true) {
//      delete
//    }
  }

  private:

   void delete_() {
//    result = ServiceResult.new success: false,
//                               result: model

//    WorkPackage.transaction {
//      descendants = model.descendants.to_a

//      result = super

//      if ( result.success?) {
//        update_ancestors_all_attributes(result.all_results).each { |ancestor_result|
//          result.merge!(ancestor_result)
//        }

//        destroy_descendants(descendants, result)
//      }

//      result
//    }

//    result
  }

//   void destroy_descendants(descendants, result) {
//    descendants.each { |descendant|
//      result.add_dependent!(ServiceResult.new(success: descendant.destroy, result: descendant))
//    }
//  }
};
}
}
}
