#pragma once
#include "composite_seeder.h"
namespace openproj {
namespace seeder {
class BasicDataSeeder : public CompositeSeeder {
public:
   virtual void data_seeder_classes()  = 0;

   void namespace_() {
//    'BasicData'
  }
};
}
}
