#ifndef JDROGON_GUI_SCRIPT_MAINHIGHIDE_H
#define JDROGON_GUI_SCRIPT_MAINHIGHIDE_H

#include <QWidget>
#include <QtWidgets>
class Script;
class MainHighScriptIDe : public QWidget {
  Q_OBJECT
 public:
  explicit MainHighScriptIDe(QWidget *parent = nullptr);

 signals:

 public slots:

 private:
  void init();
  void initAngelScript();
  Script *script;
};
class GeneralTab : public QWidget {
  Q_OBJECT

 public:
  explicit GeneralTab(const QFileInfo &fileInfo, QWidget *parent = 0);
};

//! [1]
class PermissionsTab : public QWidget {
  Q_OBJECT

 public:
  explicit PermissionsTab(const QFileInfo &fileInfo, QWidget *parent = 0);
};
//! [1]

//! [2]
class ApplicationsTab : public QWidget {
  Q_OBJECT

 public:
  explicit ApplicationsTab(const QFileInfo &fileInfo, QWidget *parent = 0);
};
//! [2]

#endif  // MAINHIGHSCRIPTIDE_H
