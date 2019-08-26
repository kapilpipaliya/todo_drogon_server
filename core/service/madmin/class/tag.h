#ifndef TAG_H
#define TAG_H


#include "../baseservice.h"
namespace madmin {
class Tag : public BaseService
{
public:
    Tag();
    void setupTable() override;
};
}
#endif // TAG_H
