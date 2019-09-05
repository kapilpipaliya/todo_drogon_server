#include "bookmark.h"

#include <utility>
using namespace  madmin;
Bookmark::Bookmark(MAdminContextPtr context_): context(std::move(context_))
{

}

void Bookmark::setupTable()
{

}
