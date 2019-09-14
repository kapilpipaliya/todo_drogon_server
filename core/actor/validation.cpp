#include "validation.h"

#include <utility>

using check_validation = caf::atom_constant<caf::atom("permis")>;
namespace actor {
Validation::Validation(caf::actor_config &cfg, nlohmann::json in)
    : caf::event_based_actor(cfg), in(std::move(in)) {
  running_job.assign([=, this](check_validation) { blocking_run(); });
}

void Validation::blocking_run() {}

caf::behavior Validation::make_behavior() {
  // start runnig
  send(this, check_validation::value);
  // also run the job when message arrive for it.
  return ([=, this](check_validation) {
    // delayed_send(this,seconds(5), check_validation::value);
    send(this, check_validation::value);
    become(running_job);
  });
}
}  // namespace actor
