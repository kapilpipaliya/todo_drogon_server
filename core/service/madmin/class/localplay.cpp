#include "localplay.h"

#include <utility>
using namespace madmin;
LocalPlay::LocalPlay(MAdminContextPtr context_)
    : context(std::move(context_)) {}

void LocalPlay::setupTable() {}
