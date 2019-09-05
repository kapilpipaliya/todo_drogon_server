#include "log.h"

#include <utility>
using namespace  madmin;
Log::Log(MAdminContextPtr context_): context(std::move(context_))
{

}

void Log::setupTable()
{

}
