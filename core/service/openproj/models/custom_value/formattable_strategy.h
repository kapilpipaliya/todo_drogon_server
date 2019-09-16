#pragma once
#include "format_strategy.h"
namespace openproj{
namespace  CustomValueN {
class
  FormattableStrategy : CustomValueN::FormatStrategy {

   void formatted_value() {
//    OpenProject::TextFormatting::Renderer.format_text value
  }

   void typed_value() {
//    value.to_s
  }

   void validate_type_of_value() {}
};
}
}
