#include "config.h"

#include <utility>
using namespace madmin;
Config::Config(MAdminContextPtr context_) : context(std::move(context_)) {}

void Config::setupTable() {}
