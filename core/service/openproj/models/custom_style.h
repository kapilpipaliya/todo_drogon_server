#pragma once
#include "activerecord.h"
#include "CustomStyles.h"
namespace openproj {
namespace models {
class CustomStyle : public openproj::models::ActiveRecord::Base, public drogon_model::openproject6::CustomStyles {
 public:
  void save(){
    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::CustomStyles> mapper_custom_styles(clientPtr);
    drogon_model::openproject6::CustomStyles* custom_styles = this;
    mapper_custom_styles.insert(*custom_styles);
  }
//  mount_uploader :logo, OpenProject::Configuration.file_uploader
//  mount_uploader :favicon, OpenProject::Configuration.file_uploader
//  mount_uploader :touch_icon, OpenProject::Configuration.file_uploader

//  class << self {
//     void current() {
//      RequestStore.fetch(:current_custom_style) {
//        custom_style = CustomStyle.order(Arel.sql("created_at DESC")).first
//        if ( custom_style.nil?) {
//          return nil
//        else
//          custom_style
//        }
//      }
//    }
//  }

   void digest() {
//    updated_at.to_i
  }

//  %i(favicon touch_icon logo).each { |name|
//    define_method "#{name}_path" {
//      image = send(name)

//      if ( image.readable?) {
//        image.local_file.path
//      }
//    }
//  }
};
}

}
