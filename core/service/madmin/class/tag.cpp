#include "tag.h"

#include <utility>
using namespace madmin;
Tag::Tag(MAdminContextPtr context_) : context(std::move(context_)) {}

void Tag::setupTable() {}
