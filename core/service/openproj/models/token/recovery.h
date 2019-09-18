#pragma once
//require_dependency 'token/base'
#include "base.h"
namespace openproj {
namespace models {
namespace Token {
  class Recovery : public Base {
    // include ExpirableToken

     void validity_time() {
//      1.day
    }
  };
}
}
}