#pragma once

#include "../baseserviceabs.h"
#include "../../../wscontroller/context/jadmincontext.h"

#define ids2(s, array)\
std::string array = "{";\
for (auto i : (s)) { array += std::to_string(i["id"].as<int>()) + ","; }\
if((s).size() > 0) array.pop_back();\
array += "}";
typedef std::shared_ptr<JAdminContext> JAdminContextPtr;
namespace jadmin {

class BaseService : public BaseServiceAbs
{
public:
    BaseService(const JAdminContextPtr &context_);
    virtual ~BaseService();
    JAdminContextPtr context;
};

}
