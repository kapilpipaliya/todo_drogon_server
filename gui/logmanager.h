#ifndef LOGMANAGER_H
#define LOGMANAGER_H
#include <string>
class QCoreApplication;
extern QCoreApplication *qtglobapp;
class LogManager
{
public:
    LogManager();

    static void sendLogMessage(const std::string &l);
    static void receiveLogMessage(const std::string &l);
};

#endif // LOGMANAGER_H
