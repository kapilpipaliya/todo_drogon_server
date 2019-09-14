#ifndef VALIDATION_H
#define VALIDATION_H

#include "caf/all.hpp"
#include "json.hpp"
namespace actor {
class Validation : public caf::event_based_actor {
 public:
  Validation(caf::actor_config &cfg, nlohmann::json in);

 protected:
  caf::behavior make_behavior() override;

 private:
  void blocking_run();

  nlohmann::json in;
  caf::behavior running_job;  // initial behavior
};
}  // namespace actor
#endif  // VALIDATION_H
