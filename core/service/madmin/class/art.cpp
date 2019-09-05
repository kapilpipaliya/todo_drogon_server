#include "art.h"

#include <utility>
using namespace madmin;
Art::Art(MAdminContextPtr context_) : context(std::move(context_)) {}

void Art::setupTable() {}
