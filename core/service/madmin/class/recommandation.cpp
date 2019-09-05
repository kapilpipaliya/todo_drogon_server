#include "recommandation.h"

#include <utility>
using namespace madmin;
Recommandation::Recommandation(MAdminContextPtr context_)
    : context(std::move(context_)) {}

void Recommandation::setupTable() {}
