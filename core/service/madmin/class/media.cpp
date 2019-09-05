#include "media.h"

#include <utility>
using namespace madmin;
Media::Media(MAdminContextPtr context_) : context(std::move(context_)) {}

void Media::setupTable() {}
