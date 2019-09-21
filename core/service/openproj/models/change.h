#pragma once
#include "activerecord.h"
namespace openproj {
namespace models {
class Change : public ActiveRecord::Base {
  // belongs_to :changeset

  // validates_presence_of :changeset_id, :action, :path
//  before_save :init_path

  // delegate :repository_encoding, to: :changeset, allow_nil: true, prefix: true

   void relative_path() {
//    changeset.repository.relative_path(path)
  }

   void path() {
    // TODO: shouldn"t access Changeset#to_utf8 directly
//    this->path = Changeset.to_utf8(read_attribute(:path), changeset_repository_encoding)
  }

   void from_path() {
    // TODO: shouldn"t access Changeset#to_utf8 directly
//    this->from_path = Changeset.to_utf8(read_attribute(:from_path), changeset_repository_encoding)
  }

   void init_path() {
//    this->path ||= ""
  }
};
}

}