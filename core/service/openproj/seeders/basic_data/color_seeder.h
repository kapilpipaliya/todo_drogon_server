#pragma once
#include <drogon/drogon.h>
#include <vector>
#include "../seeder.h"
#include "models/Colors.h"
namespace openproj {
namespace seeder {
namespace BasicData {
class ColorSeeder : public Seeder {
  struct row {
    std::string name;
    std::string hexcode;
  };
  std::vector<row> data_;

 public:
  void seed_data() {
    //      Color.transaction {
    //        data.each { |attributes|
    //          Color.create(attributes)
    //        }
    //      }

    auto clientPtr = drogon::app().getDbClient("sce");
    for (auto &it : data()) {
      drogon::orm::Mapper<drogon_model::openproject6::Colors> mapper(clientPtr);
      drogon_model::openproject6::Colors color;
      color.setName(it.name);
      color.setHexcode(it.hexcode);
      mapper.insert(color);
    }
  }

  bool applicable() {
    //      Color.all.empty?
  }

  void not_applicable_message() {
    //      'Skipping colors as there are already some configured'
  }

  std::vector<row> data() {
    //      [
    //        { name: I18n.t(:default_color_blue_dark),   hexcode: '#175A8E' },
    //        { name: I18n.t(:default_color_blue),        hexcode: '#1A67A3' },
    //        { name: I18n.t(:default_color_blue_light),  hexcode: '#00B0F0' },
    //        { name: I18n.t(:default_color_green_light), hexcode: '#35C53F' },
    //        { name: I18n.t(:default_color_green_dark),  hexcode: '#339933' },
    //        { name: I18n.t(:default_color_yellow),      hexcode: '#FFFF00' },
    //        { name: I18n.t(:default_color_orange),      hexcode: '#FFCC00' },
    //        { name: I18n.t(:default_color_red),         hexcode: '#FF3300' },
    //        { name: I18n.t(:default_color_magenta),     hexcode: '#E20074' },
    //        { name: I18n.t(:default_color_white),       hexcode: '#FFFFFF' },
    //        { name: I18n.t(:default_color_grey_light),  hexcode: '#F8F8F8' },
    //        { name: I18n.t(:default_color_grey),        hexcode: '#EAEAEA' },
    //        { name: I18n.t(:default_color_grey_dark),   hexcode: '#878787' },
    //        { name: I18n.t(:default_color_black),       hexcode: '#000000' }
    //      ]
    data_.insert(data_.end(), {{name : "Blue (dark)", hexcode : "#175A8E"},
                               {name : "Blue", hexcode : "#1A67A3"},
                               {name : "Blue (light)", hexcode : "#00B0F0"},
                               {name : "Green (light)", hexcode : "#35C53F"},
                               {name : "Green (dark)", hexcode : "#339933"},
                               {name : "Yellow", hexcode : "#FFFF00"},
                               {name : "Orange", hexcode : "#FFCC00"},
                               {name : "Red", hexcode : "#FF3300"},
                               {name : "Magenta", hexcode : "#E20074"},
                               {name : "White", hexcode : "#FFFFFF"},
                               {name : "Grey (light)", hexcode : "#F8F8F8"},
                               {name : "Grey", hexcode : "#EAEAEA"},
                               {name : "Grey (dark)", hexcode : "#878787"},
                               {name : "Black", hexcode : "#000000"}});
    return data_;
  }
};
}  // namespace BasicData
}  // namespace seeder
}  // namespace openproj
