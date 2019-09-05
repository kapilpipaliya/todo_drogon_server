#include "mailer.h"

#include <utility>
using namespace madmin;
Mailer::Mailer(MAdminContextPtr context_) : context(std::move(context_)) {}

void Mailer::setupTable() {}
