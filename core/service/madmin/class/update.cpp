#include "update.h"

#include <utility>
using namespace madmin;
Update::Update(MAdminContextPtr context_) : context(std::move(context_)) {}

void Update::setupTable() {}
