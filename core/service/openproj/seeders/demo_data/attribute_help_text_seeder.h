#pragma once
#include "../seeder.h"
namespace openproj {
namespace seeder {
namespace DemoData {
  class AttributeHelpTextSeeder : public Seeder {
  public:
     AttributeHelpTextSeeder() {}

     void seed_data() {
//      LOG_DEBUG << "    ↳ Creating attribute help texts"

      seed_attribute_help_texts();

//      puts
    }

    private:

     void seed_attribute_help_texts() {
//      help_texts = demo_data_for("attribute_help_texts")
//      if ( help_texts.present?) {
//        help_texts.each { |help_text_attr|
//          LOG_DEBUG << "."
//          create_attribute_help_text help_text_attr
//        }
//      }
    }

//     void create_attribute_help_text(help_text_attr) {
//      help_text_attr[:type] = AttributeHelpTextN::WorkPackage

//      attribute_help_text = AttributeHelpText.new help_text_attr
//      attribute_help_text.save
//    }
  };
}
}
}
