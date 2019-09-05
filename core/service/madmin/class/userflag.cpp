#include "userflag.h"

#include <utility>
using namespace  madmin;
UserFlag::UserFlag(MAdminContextPtr context_): context(std::move(context_))
{

}

void UserFlag::setupTable()
{

}
