#include "./logmanager.h"
#include <QApplication>
#include "./widgets/dgraphlog/dgraphlog.h"
QCoreApplication *qtglobapp = nullptr;
LogManager::LogManager() {}

void LogManager::sendLogMessage(const std::string &l) {
  if (widgets::dgraphlog) {
    widgets::dgraphlog->addSendLog(l);
    widgets::dgraphlog->update();
    qtglobapp->processEvents();
    // QCoreApplication *qtglobapp = QCoreApplication::instance();
  }
}

void LogManager::receiveLogMessage(const std::string &l) {
  if (widgets::dgraphlog) {
    widgets::dgraphlog->addReceiveLog(l);
  }
}
