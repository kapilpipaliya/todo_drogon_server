#pragma once
#include "../seeder.h"
#include <drogon/drogon.h>
#include "models/Statuses.h"
#include "models/Colors.h"
namespace openproj {
namespace seeder {
namespace BasicData {
  class StatusSeeder : public Seeder {
    public:
      struct row {
        std::string name;
        std::string color_name;
        bool is_closed;
        bool is_default;
        int position;
      };
      std::vector<row> data_;



     void seed_data() {
//      Status.transaction {
//        data.each { |attributes|
//          Status.create!(attributes)
//        }
//      }
         auto clientPtr = drogon::app().getDbClient("sce");
         for (auto &it : data()) {
           drogon::orm::Mapper<drogon_model::openproject4::Statuses> mapper(clientPtr);

           drogon::orm::Mapper<drogon_model::openproject4::Colors> mapper_color(clientPtr);
           auto r = mapper_color.findBy(
                Criteria(drogon_model::openproject4::Colors::Cols::_name, CompareOperator::EQ, it.color_name));

           drogon_model::openproject4::Statuses status;
           status.setName(it.name);
           status.setColorId(*r.at(0).getId());
           status.setIsClosed(it.is_closed);
           status.setIsDefault(it.is_default);
           status.setPosition(it.position);
           mapper.insert(status);
         }

    }

     bool applicable() {
//      Status.all.any?
    }

     void not_applicable_message() {
//      'Skipping statuses - already exists/configured'
    }

     virtual std::vector<row> data()  = 0;
  };
}
}
}
