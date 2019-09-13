require_dependency 'token/base'

namespace Token {
  class Rss : public Base {
    after_initialize {
      unless value.present?
        this->value = this->class.generate_token_value
      }
    }

     void plain_value() {
      value
    }
  }
}
