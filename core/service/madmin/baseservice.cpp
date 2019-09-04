#include "baseservice.h"

#include "../../sql/query.h"

using namespace  madmin;
BaseService::BaseService(const MAdminContextPtr &context_): context(context_)
{  }
BaseService::~BaseService() {  }

