#pragma once
#include "activerecord.h"
namespace openproj {
namespace models {
class RolePermission : public ActiveRecord::Base {
  // belongs_to :role

  // validates_presence_of :permission
};
}

}