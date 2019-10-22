#pragma once
//require_dependency "token/hashed_token"
#include "hashed_token.h"
namespace openproj {
namespace models {
namespace Token {
  class AutoLogin : public HashedToken {
  };
}
}
}