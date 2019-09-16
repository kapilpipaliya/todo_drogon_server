#pragma once
//require_dependency 'token/base'
#include "base.h"
namespace openproj {
namespace Token {
  class Recovery : public Base {
    // include ExpirableToken

     void validity_time() {
//      1.day
    }
  };
}
}
