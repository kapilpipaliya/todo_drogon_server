#ifndef UPLOAD_H
#define UPLOAD_H


#include "../baseservice.h"
namespace madmin {
class Upload : public BaseService
{
public:
    Upload(const MAdminContextPtr &);
    void setupTable() override;
};
}
#endif // UPLOAD_H
