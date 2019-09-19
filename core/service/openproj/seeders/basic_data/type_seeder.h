#pragma once
#include "../seeder.h"
#include <drogon/drogon.h>
#include "models/Colors.h"
#include "models/Types.h"

namespace openproj {
namespace seeder {
namespace BasicData {
  class TypeSeeder : public Seeder {
   //   INSERT INTO "types" ("name", "position", "is_in_roadmap", "is_default", "color_id",
  public:
    struct row {
      std::string name;
      int position;
      bool is_default;
      long color_id;
      bool is_in_roadmap;
      bool is_milestone;
      std::string description;
    };
    std::vector<row> data_;
     void seed_data() {
//      Type.transaction {
//        data.each { |attributes|
//          Type.create!(attributes)
//        }
//      }
         auto clientPtr = drogon::app().getDbClient("sce");
         for (auto &it : data()) {
           drogon::orm::Mapper<drogon_model::openproject4::Types> mapper(clientPtr);

           drogon_model::openproject4::Types type;
           type.setName(it.name);
           type.setPosition(it.position);
           type.setIsDefault(it.is_default);
           type.setColorId(it.color_id);
           type.setIsInRoadmap(it.is_in_roadmap);
           type.setIsMilestone(it.is_milestone);
           type.setDescription(it.description);
           mapper.insert(type);
         }
    }

     bool applicable() {
//      Type.all.any?
    }

     void not_applicable_message() {
//      'Skipping types - already exists/configured'
    }

    //
    // Returns the data of all types to seed.
    //
    // @return [Array<Hash>] List of attributes for each type.
     std::vector<row> data() {
//      colors = Color.all
//      colors = colors.map { |c| { c.name =>  c.id } }.reduce({}, :merge)

//      type_table.map { |_name, values|
//        color_id = Color.find_by(id: values[2]) ? values[2] : colors[I18n.t(values[2])]

//        {
//          name:                 I18n.t(values[5]),
//          position:             values[0],
//          is_default:           values[1],
//          color_id:             color_id,
//          is_in_roadmap:        values[3],
//          is_milestone:         values[4],
//          description:          type_description(values[5])
//        }
//      }

        auto clientPtr = drogon::app().getDbClient("sce");
        drogon::orm::Mapper<drogon_model::openproject4::Colors> mapper(clientPtr);
        auto colors = mapper.findAll();

        for (auto &it : type_table()) {
            auto position = std::get<0>(it.second);
            auto is_default = std::get<1>(it.second);
            auto color_name = std::get<2>(it.second);
            auto is_in_roadmap = std::get<3>(it.second);
            auto is_milestone = std::get<4>(it.second);
            auto description = std::get<5>(it.second);
            auto r = mapper.findBy(
                 Criteria(drogon_model::openproject4::Colors::Cols::_name, CompareOperator::EQ, color_name));
            data_.push_back({
                                description, position, is_default,*r.at(0).getId(), is_in_roadmap, is_milestone, description
                            });
            return data_;
        }
    }

     virtual std::vector<std::string> type_names()  = 0;

     virtual std::map<std::string, std::tuple<int, bool, std::string, bool, bool, std::string> >type_table()  = 0;

//     void type_description(type_name) {
//      if ( demo_data_for('type_configuration').nil?) { return '' ;}

//      demo_data_for('type_configuration').each { |entry|
//        if ( entry[:type] && I18n.t(entry[:type]) === I18n.t(type_name)) {
//          return entry[:description] ? entry[:description] : ''
//        else
//          return ''
//        }
//      }
//    }

//     void set_attribute_groups_for_type(type) {
//      if ( demo_data_for('type_configuration').nil?) { return ;}

//      demo_data_for('type_configuration').each { |entry|
//        if ( entry[:form_configuration] && I18n.t(entry[:type]) === type.name) {

//          entry[:form_configuration].each { |form_config_attr|
//            groups = type.default_attribute_groups
//            query_association = 'query_' + find_query_by_name(form_config_attr[:query_name]).to_s
//            groups.unshift([form_config_attr[:group_name], [query_association.to_sym]])

//            type.attribute_groups = groups
//          }

//          type.save!
//        }
//      }
//    }

    private:

//     void find_query_by_name(name) {
//      Query.find_by(name: name).id
//    }
  };
}
}
}

