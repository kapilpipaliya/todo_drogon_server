#include "stats.h"

#include <utility>
using namespace madmin;
Stats::Stats(MAdminContextPtr context_) : context(std::move(context_)) {}

void Stats::setupTable() {}
