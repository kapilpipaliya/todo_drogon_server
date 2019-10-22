#pragma once
#include "../../../queries/work_packages/filter/attachment_base_filter.h"
namespace openproj {
namespace models {
namespace Queries {
namespace WorkPackages {
namespace Filter {
class AttachmentContentFilter : public openproj::models::Queries::WorkPackages::Filter::AttachmentBaseFilter {
   void key() {
//    :attachment_content
  }

   void name() {
//    :attachment_content
  }

   void human_name() {
//    Attachment.human_attribute_name("attachment_content")
  }

   void search_column() {
//    "fulltext"
  }
};
}
}
}
}

}