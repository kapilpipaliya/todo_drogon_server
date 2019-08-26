#ifndef UI_H
#define UI_H


#include "../baseservice.h"
namespace madmin {
class UI : public BaseService
{
public:
    UI();
    void setupTable() override;
};
}
#endif // UI_H
