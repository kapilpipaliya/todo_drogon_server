#ifndef OPENPROJ_MODELS_ORDERED_WORK_PACKAGE_H
#define OPENPROJ_MODELS_ORDERED_WORK_PACKAGE_H


#include "application_record.h"
#include "OrderedWorkPackages.h"

namespace openproj {

namespace models {

class OrderedWorkPackage : public ApplicationRecord, public drogon_model::openproject6::OrderedWorkPackages {
 public:
  void save(){
    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::OrderedWorkPackages> mapper_ordered_work_packages(clientPtr);
    drogon_model::openproject6::OrderedWorkPackages* ordered_work_packages = this;
    mapper_ordered_work_packages.insert(*ordered_work_packages);
  }
  // belongs_to :query
  // belongs_to :work_package

  //  acts_as_list scope: :query, top_of_list: 0
};

} // namespace openproj::models

} // namespace openproj
#endif
