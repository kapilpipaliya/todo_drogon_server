#include "search.h"

#include <utility>
using namespace madmin;
Search::Search(MAdminContextPtr context_) : context(std::move(context_)) {}

void Search::setupTable() {}
