#include "playlistbase.h"

#include <utility>
using namespace madmin;
PlayListBase::PlayListBase(MAdminContextPtr context_)
    : context(std::move(context_)) {}

void PlayListBase::setupTable() {}
