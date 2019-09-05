#include "access.h"

#include <utility>
using namespace madmin;
Access::Access(MAdminContextPtr context_) : context(std::move(context_)) {}

void Access::setupTable() {}
