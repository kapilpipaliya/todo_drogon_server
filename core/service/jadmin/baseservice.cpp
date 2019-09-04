#include "baseservice.h"

#include "../../sql/query.h"

using namespace  jadmin;
BaseService::BaseService(const JAdminContextPtr &context_): context(context_)
{  }
BaseService::~BaseService() {  }
