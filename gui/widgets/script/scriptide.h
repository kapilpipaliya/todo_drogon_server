#ifndef JDROGON_GUI_SCRIPT_MAINHIGHIDE_H
#define JDROGON_GUI_SCRIPT_MAINHIGHIDE_H

#include <QWidget>
#include <QtWidgets>
class Script; // anglescript forward
namespace widgets {
class ScriptIde : public QWidget {
  Q_OBJECT
 public:
  explicit ScriptIde(QWidget *parent = nullptr);
  static void sendmsg();

 signals:

 public slots:

 private:
  void init();
  void initAngelScript();
  Script *script;
};
}
#endif  // ScriptIde_H
