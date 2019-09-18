#pragma once
#include "../../../queries/work_packages/filter/attachment_base_filter.h"
namespace openproj {
namespace models {
namespace Queries {
namespace WorkPackages {
namespace Filter {
class AttachmentFileNameFilter : public openproj::models::Queries::WorkPackages::Filter::AttachmentBaseFilter {
   void key() {
//    :attachment_file_name
  }

   void name() {
//    :attachment_file_name
  }

   void human_name() {
//    Attachment.human_attribute_name('attachment_file_name')
  }

   void search_column() {
//    'file'
  }

   void normalization_type() {
//    :filename
  }
};
}
}
}
}

}