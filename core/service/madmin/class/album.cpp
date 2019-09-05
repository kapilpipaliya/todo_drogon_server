#include "album.h"

#include <utility>
using namespace madmin;
Album::Album(MAdminContextPtr context_) : context(std::move(context_)) {}

void Album::setupTable() {}
