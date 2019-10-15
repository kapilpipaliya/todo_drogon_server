#ifndef MAINWINHIGH_H
#define MAINWINHIGH_H
#include "./MdiMainWindow/mainwindow.h"

class MainWinHigh : public MainWindow {
 public:
  MainWinHigh(QWidget *parent = nullptr);
 private slots:
  void adminLoggedIn();
  void userLoggedIn();
  void save() override;
  void newFile() override;
  void showConfigDialog();
  QWidget *createMdiChild() override;
  void addMdiChild(QWidget *);

 private:
  QToolBar *configToolBar;
};

#endif  // MAINWINHIGH_H
