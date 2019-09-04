#ifndef JOURNALTYPE_H
#define JOURNALTYPE_H
#include "../baseservice.h"
namespace jadmin {
class JournalType : public BaseService
{
public:
    JournalType(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // JOURNALTYPE_H