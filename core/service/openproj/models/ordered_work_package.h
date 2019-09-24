#ifndef OPENPROJ_MODELS_ORDERED_WORK_PACKAGE_H
#define OPENPROJ_MODELS_ORDERED_WORK_PACKAGE_H


#include "application_record.h"
#include "OrderedWorkPackages.h"

namespace openproj {

namespace models {

class OrderedWorkPackage : public ApplicationRecord, public drogon_model::openproject6::OrderedWorkPackages {
  // belongs_to :query
  // belongs_to :work_package

  //  acts_as_list scope: :query, top_of_list: 0
};

} // namespace openproj::models

} // namespace openproj
#endif
