#pragma once
#include "composite_seeder.h"
namespace openproj {
namespace seeder {
class DemoDataSeeder : public CompositeSeeder {
public:
   void data_seeder_classes() {
//    [
//      DemoData::GroupSeeder,
//      DemoData::AttributeHelpTextSeeder,
//      DemoData::GlobalQuerySeeder,
//      DemoData::ProjectSeeder
//    ]
  }

   void namespace_() {
//    'DemoData'
  }
};
}
}
