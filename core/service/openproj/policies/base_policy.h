class BasePolicy
  // attr_accessor :user

   BasePolicy(user) {
    this->user = user
  }

   void actions(wp) {
    cache[wp].each_with_object([]) { |(k, v), a| a << k if ( v }) {
  }

   void allowed?(object, action) {
    cache(object)[action]
  }
}
