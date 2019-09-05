#include "tmpplaylist.h"

#include <utility>
using namespace madmin;
TmpPlayList::TmpPlayList(MAdminContextPtr context_)
    : context(std::move(context_)) {}

void TmpPlayList::setupTable() {}
