#include "share.h"

#include <utility>
using namespace  madmin;
Share::Share(MAdminContextPtr context_): context(std::move(context_))
{

}

void Share::setupTable()
{

}
