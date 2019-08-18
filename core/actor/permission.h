#ifndef PERMISSION_H
#define PERMISSION_H

#include "caf/all.hpp"
#include "json.hpp"

class Permission : public caf::event_based_actor
{
public:
    Permission( caf::actor_config &cfg, nlohmann::json in);
private:
    void blocking_run();

    nlohmann::json  in;
    caf:: behavior    running_job; // initial behavior
protected:
   caf::behavior make_behavior() override;
};

#endif // PERMISSION_H
