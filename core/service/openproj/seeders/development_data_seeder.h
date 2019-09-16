#pragma once
#include "composite_seeder.h"

namespace openproj {
namespace seeder {
class DevelopmentDataSeeder : public CompositeSeeder {
public:
   void data_seeder_classes() {
//    [
//      DevelopmentData::UsersSeeder,
//      DevelopmentData::CustomFieldsSeeder,
//      DevelopmentData::ProjectsSeeder,
//      //DevelopmentData::WorkPackageSeeder
//    ]
  }

   void namespace_() {
//    'DevelopmentData'
  }
};
}
}
