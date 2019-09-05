#include "useractivity.h"

#include <utility>
using namespace  madmin;
UserActivity::UserActivity(MAdminContextPtr context_): context(std::move(context_))
{

}

void UserActivity::setupTable()
{

}
