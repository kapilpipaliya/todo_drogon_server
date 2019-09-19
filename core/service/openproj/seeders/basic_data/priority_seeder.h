#pragma once
#include <drogon/drogon.h>
#include <vector>
#include "../seeder.h"
#include "models/Colors.h"
#include "models/Enumerations.h"
namespace openproj {
namespace seeder {
namespace BasicData {
  class PrioritySeeder : public Seeder {
  public:
    struct row {
      std::string name;
      std::string color_name;
      int position;
      bool is_default;
    };
    std::vector<row> data_;
     void seed_data() {
//      IssuePriority.transaction {
//        data.each { |attributes|
//          IssuePriority.create!(attributes)
//        }
//      }

       auto clientPtr = drogon::app().getDbClient("sce");
       for (auto &it : data()) {
         drogon::orm::Mapper<drogon_model::openproject6::Enumerations> mapper(clientPtr);
         drogon::orm::Mapper<drogon_model::openproject6::Colors> mapper_color(clientPtr);
         auto r = mapper_color.findBy(
              Criteria(drogon_model::openproject6::Colors::Cols::_name, CompareOperator::EQ, it.color_name));

         drogon_model::openproject6::Enumerations enumeration;
         enumeration.setName(it.name);
         enumeration.setColorId(*r.at(0).getId());
         enumeration.setPosition(it.position);
         enumeration.setIsDefault(it.is_default);
         enumeration.setType("IssuePriority");
         enumeration.setActive(false); //this is default
         mapper.insert(enumeration);
       }
    }

     bool applicable() {
//      IssuePriority.all.empty?
    }

     void not_applicable_message() {
//      'Skipping priorities as there are already some configured'
    }

     virtual  std::vector<row>  data()  = 0;
  };
}
}
}
