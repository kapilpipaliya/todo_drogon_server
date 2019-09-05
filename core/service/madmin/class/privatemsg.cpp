#include "privatemsg.h"

#include <utility>
using namespace  madmin;
PrivateMsg::PrivateMsg(MAdminContextPtr context_): context(std::move(context_))
{

}

void PrivateMsg::setupTable()
{

}
