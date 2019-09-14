require_dependency 'token/base'

namespace Token {
  class Recovery : public Base {
    // include ExpirableToken

     void validity_time() {
      1.day
    }
  }
}
