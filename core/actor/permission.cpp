#include "permission.h"

using check_permission = caf::atom_constant<caf::atom("permis")>;

Permission::Permission(caf::actor_config &cfg, nlohmann::json in) : caf::event_based_actor(cfg), in(in)
{
    running_job.assign(
      [=, this](check_permission) {
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
        send(this, check_permission::value);
        // also run the job when message arrive for it.
        return (
          [=, this](check_permission) {
            //delayed_send(this,seconds(5), check_permission::value);
            send(this, check_permission::value);
            become(running_job);
          }
        );
}
