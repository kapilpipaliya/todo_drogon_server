#pragma once
#include <drogon/drogon.h>
#include "../seeder.h"
//#include "../../models/time_entry_activity.h"
#include "models/Enumerations.h"

namespace openproj {
namespace seeder {
namespace BasicData {
class ActivitySeeder : public Seeder {
 public:
  struct row {
    std::string name;
    int position;
    bool is_default;
  };
  void seed_data() {
    //      TimeEntryActivity.transaction {
    //        data.each { |attributes|
    //          TimeEntryActivity.create(attributes)
    //        }
    //      }

    auto clientPtr = drogon::app().getDbClient("sce");
    for (auto &it : data2()) {
      drogon::orm::Mapper<drogon_model::openproject6::Enumerations> mapper(
          clientPtr);

      drogon_model::openproject6::Enumerations enumeration;
      enumeration.setName(it.name);
      enumeration.setPosition(it.position);
      enumeration.setType("TimeEntryActivity");
      enumeration.setIsDefault(it.is_default);
      enumeration.setActive(true);  // this is default
      enumeration.setCreatedAt(trantor::Date::now());
      enumeration.setUpdatedAt(trantor::Date::now());
      mapper.insert(enumeration);
    }
  }

  bool applicable() {
    //      TimeEntryActivity.all.empty?
    return true;
  }

  void not_applicable_message() {
    //      "Skipping activities as there are already some configured"
  }

  //     virtual void data()  = 0;
  void data() {}
  virtual std::vector<row> data2() = 0;
};
}  // namespace BasicData
}  // namespace seeder
}  // namespace openproj
