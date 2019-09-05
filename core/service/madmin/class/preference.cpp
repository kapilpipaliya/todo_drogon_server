#include "preference.h"

#include <utility>
using namespace  madmin;
Preference::Preference(MAdminContextPtr context_): context(std::move(context_))
{

}

void Preference::setupTable()
{

}
