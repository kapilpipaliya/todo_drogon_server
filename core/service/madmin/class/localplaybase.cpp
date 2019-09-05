#include "localplaybase.h"

#include <utility>
using namespace  madmin;
LocalPlayBase::LocalPlayBase(MAdminContextPtr context_): context(std::move(context_))
{

}

void LocalPlayBase::setupTable()
{

}
