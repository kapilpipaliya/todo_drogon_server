#include "random.h"

#include <utility>
using namespace madmin;
Random::Random(MAdminContextPtr context_) : context(std::move(context_)) {}

void Random::setupTable() {}
