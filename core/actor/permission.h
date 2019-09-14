#ifndef PERMISSION_H
#define PERMISSION_H

#include "caf/all.hpp"
#include "json.hpp"
namespace actor {
class Permission : public caf::event_based_actor {
 public:
  Permission(caf::actor_config &cfg, nlohmann::json in);

 protected:
  caf::behavior make_behavior() override;

 private:
  void blocking_run();

  nlohmann::json in;
  caf::behavior running_job;  // initial behavior
};
}  // namespace actor
#endif  // PERMISSION_H
