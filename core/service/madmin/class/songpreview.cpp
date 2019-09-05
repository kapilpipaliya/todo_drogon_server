#include "songpreview.h"

#include <utility>
using namespace madmin;
SongPreview::SongPreview(MAdminContextPtr context_)
    : context(std::move(context_)) {}

void SongPreview::setupTable() {}
