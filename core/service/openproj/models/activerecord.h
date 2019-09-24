#ifndef ACTIVERECORD_H
#define ACTIVERECORD_H
#include <drogon/drogon.h>
namespace openproj {
namespace models {
namespace ActiveRecord {
class Base {
 protected:
  virtual void before_validation() {}
  virtual void after_validation() {}
  virtual void before_save() {}
  virtual void around_save() {}
  virtual void after_save() {}
  virtual void after_commit() {}
  virtual void after_rollback() {}
  // create
  virtual void before_create() {}
  virtual void around_create() {}
  virtual void after_create() {}

  // Updating an Object
  virtual void before_update() {}
  virtual void around_update() {}
  virtual void after_update() {}


  // Destroying an Object
  virtual void before_destroy() {}
  virtual void around_destroy() {}
  virtual void after_destroy() {}
};
}
}
}
#endif // ACTIVERECORD_H
