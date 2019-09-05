#include "api.h"

#include <utility>
using namespace madmin;
Api::Api(MAdminContextPtr context_) : context(std::move(context_)) {}

void Api::setupTable() {}
