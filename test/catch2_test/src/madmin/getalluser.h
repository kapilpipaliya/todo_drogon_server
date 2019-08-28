#ifndef GETALLUSER_H
#define GETALLUSER_H

#include "../wstestbase.h"
namespace madmin {
class getAllUser: public WSTestBase
{
protected:
void connectToServer();
void setMessageHandler();
};
}
#endif // GETALLUSER_H
