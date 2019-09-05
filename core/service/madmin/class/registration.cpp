#include "registration.h"

#include <utility>
using namespace madmin;
Registration::Registration(MAdminContextPtr context_)
    : context(std::move(context_)) {}

void Registration::setupTable() {}
