#include "upload.h"

#include <utility>
using namespace madmin;
Upload::Upload(MAdminContextPtr context_) : context(std::move(context_)) {}

void Upload::setupTable() {}
