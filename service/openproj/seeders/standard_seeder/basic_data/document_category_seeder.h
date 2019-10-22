#pragma once
#include <string>
#include <vector>
#include "../../basic_data/document_category_seeder.h"

#include <map>
namespace openproj {
namespace seeder {
namespace StandardSeeder {
namespace BasicData {
class DocumentCategorySeeder : public seeder::BasicData::DocumentCategorySeeder {
 public:
  std::vector<row> data() {
    //["documentation", "specification", "other"]

    // todo: doing batch search is good too here for color_id;
    data_.insert(data_.end(),
                 {{"Documentation"}, {"Specification"}, {"Other"}});
    return data_;
  }
};
}  // namespace BasicData
}  // namespace StandardSeeder
}  // namespace seeder
}  // namespace openproj
