#pragma once
#include <drogon/drogon.h>
#include <vector>
#include "../seeder.h"
#include "models/Colors.h"
#include "models/Enumerations.h"

namespace openproj {
namespace seeder {
namespace BasicData {
class DocumentCategorySeeder : public Seeder {
 public:
  struct row {
    std::string name;
  };
  std::vector<row> data_;

  void seed_data() {
    auto clientPtr = drogon::app().getDbClient("sce");
    for (auto &it : data()) {
      drogon::orm::Mapper<drogon_model::openproject6::Enumerations> mapper(
          clientPtr);


      drogon_model::openproject6::Enumerations enumeration;
      enumeration.setName(it.name);
      enumeration.setType("DocumentCategory");
      enumeration.setActive(false);  // this is default
      enumeration.setIsDefault(false); // this is default
      enumeration.setCreatedAt(trantor::Date::now());
      enumeration.setUpdatedAt(trantor::Date::now());
      mapper.insert(enumeration);
    }
  }

  bool applicable() {
    //      Status.all.any?
  }

  void not_applicable_message() {
    //      'Skipping statuses - already exists/configured'
  }

  virtual std::vector<row> data() = 0;
};
}  // namespace BasicData
}  // namespace seeder
}  // namespace openproj
