#ifndef TONE_H
#define TONE_H
#include "../baseservice.h"
namespace jadmin {
class Tone : public BaseService
{
public:
    Tone(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // TONE_H