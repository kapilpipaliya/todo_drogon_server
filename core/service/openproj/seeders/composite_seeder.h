#pragma once
#include "seeder.h"
namespace openproj {
namespace seeder {
class CompositeSeeder : public Seeder {
public:
   void seed_data() {
//    ActiveRecord::Base.transaction {
//      data_seeders.each { |seeder|
//        puts " ↳ #{seeder.class.name.demodulize}"
//        seeder.seed!
//      }
       for (auto it : data_seeder_classes()) {
           it->seed();
       }

//      if ( discovered_seeders.empty?) { return ;}

//      puts "   Loading discovered seeders: "
//      discovered_seeders.each { |seeder|
//        puts " ↳ #{seeder.class.name.demodulize}"
//        seeder.seed!
//      }
//    }
  }

   void data_seeders() {
//    data_seeder_classes.map(&:new)
  }

   virtual std::vector<std::shared_ptr<openproj::seeder::Seeder>>  data_seeder_classes() = 0;

   void discovered_seeders() {
//    discovered_seeder_classes.map(&:new)
  }

  //
  // Discovered seeders defined outside of the core (i.e. in plugins).
  //
  // Seeders defined in the core have a simple namespace, e.g. 'BasicData'
  // or 'DemoData'. Plugins must define their seeders in their own namespace,
  // e.g. 'BasicData::Documents' in order to avoid name conflicts.
//   void discovered_seeder_classes() {
//    Seeder
//      .subclasses
//      .reject { |cl| cl.to_s.deconstantize == namespace }
//      .select { |cl| include_discovered_class? cl }
//  }

   virtual std::string namespace_() = 0;

  //
  // Accepts plugin seeders, e.g. 'BasicData::Documents'.
//   void include_discovered_class?(discovered_class) {
//    discovered_class.name =~ /^#{namespace}::/
//  }
};
}
}
