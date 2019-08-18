#include "permission.h"

using run_atom = caf::atom_constant<caf::atom("permis")>;

Permission::Permission(caf::actor_config &cfg, nlohmann::json in) : caf::event_based_actor(cfg), in(in)
{
    running_job.assign(
      [=, this](run_atom) {
        blocking_run();
      }
    );
}

void Permission::blocking_run()
{

}

caf::behavior Permission::make_behavior()
{
    // start runnig
        send(this, run_atom::value);
        // also run the job when message arrive for it.
        return (
          [=, this](run_atom) {
            //delayed_send(this,seconds(5), run_atom::value);
            send(this, run_atom::value);
            become(running_job);
          }
        );
}
