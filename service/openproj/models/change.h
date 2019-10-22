#ifndef OPENPROJ_MODELS_CHANGE_H
#define OPENPROJ_MODELS_CHANGE_H


#include "activerecord.h"
#include "Changes.h"

namespace openproj {

namespace models {

class Change : public openproj::models::ActiveRecord::Base, public drogon_model::openproject6::Changes {
 public:
  void save(){
    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::Changes> mapper_changes(clientPtr);
    drogon_model::openproject6::Changes* changes = this;
    mapper_changes.insert(*changes);
  }
  public:
    // belongs_to :changeset
    // validates_presence_of :changeset_id, :action, :path
    //  before_save :init_path
    // delegate :repository_encoding, to: :changeset, allow_nil: true, prefix: true
    inline void relative_path() {
    //    changeset.repository.relative_path(path)
      };

    inline void path() {
        // TODO: shouldn"t access Changeset#to_utf8 directly
    //    this->path = Changeset.to_utf8(read_attribute(:path), changeset_repository_encoding)
      };

    inline void from_path() {
        // TODO: shouldn"t access Changeset#to_utf8 directly
    //    this->from_path = Changeset.to_utf8(read_attribute(:from_path), changeset_repository_encoding)
      };

    inline void init_path() {
    //    this->path ||= ""
      };

};

} // namespace openproj::models

} // namespace openproj
#endif
