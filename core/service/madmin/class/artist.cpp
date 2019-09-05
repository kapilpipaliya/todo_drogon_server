#include "artist.h"

#include <utility>
using namespace madmin;
Artist::Artist(MAdminContextPtr context_) : context(std::move(context_)) {}

void Artist::setupTable() {}
