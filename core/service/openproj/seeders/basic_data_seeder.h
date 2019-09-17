#pragma once
#include "composite_seeder.h"
#include <string>
namespace openproj {
namespace seeder {
class BasicDataSeeder : public CompositeSeeder {
public:
   virtual std::vector<std::shared_ptr<openproj::seeder::Seeder>>   data_seeder_classes()  = 0;

   std::string namespace_() {
    return "BasicData";
  }
};
}
}
