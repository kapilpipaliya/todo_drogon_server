#pragma once
#include "activerecord.h"
#include "JournalVersions.h"
namespace openproj {
namespace models {
class JournalVersion : public openproj::models::ActiveRecord::Base, public drogon_model::openproject6::JournalVersions {
 public:
  void save(){
    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::JournalVersions> mapper_journal_versions(clientPtr);
    drogon_model::openproject6::JournalVersions* journal_versions = this;
    mapper_journal_versions.insert(*journal_versions);
  }
};
}

}
