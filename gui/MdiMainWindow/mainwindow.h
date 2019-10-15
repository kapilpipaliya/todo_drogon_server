#ifndef MAINWINDOW_REAL_MAIN_WINDOW_H
#define MAINWINDOW_REAL_MAIN_WINDOW_H

#include <QMainWindow>

class QAction;
class QMenu;
class QMdiArea;
class QMdiSubWindow;
class QSignalMapper;
class QLabel;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  QMdiArea *mdiArea;

 protected:
  void closeEvent(QCloseEvent *event);

 public slots:
  virtual void newFile() {}
  virtual void save() {}
  virtual void about();
  void updateMenus();
  void updateWindowMenu();
  virtual QWidget *createMdiChild() {}
  void switchLayoutDirection();
  void setActiveSubWindow(QWidget *window);
  void showStatusMessage(QString);

 private:
  void InitForm();
  void createActions();
  void createMenus();
  void createToolBars();
  void createStatusBar();
  void readSettings();
  void writeSettings();
  QWidget *activeMdiChild();
  QMdiSubWindow *findMdiChild(const QString &fileName);

  // QMdiArea *mdiArea;
  QSignalMapper *windowMapper;

  QMenu *fileMenu;
  QMenu *configMenu;
  QMenu *windowMenu;
  QMenu *helpMenu;

  QToolBar *fileToolBar;

  QAction *newAct;
  QAction *saveAct;
  QAction *exitAct;

  QAction *configAct;

  QAction *closeAct;
  QAction *closeAllAct;
  QAction *tileAct;
  QAction *cascadeAct;
  QAction *nextAct;
  QAction *previousAct;
  QAction *separatorAct;

  QAction *aboutAct;

 private:
  QTimer *myTimer;
  QLabel *dateLabel;
  QLabel *timeLabel;
 private slots:
  void SetTime();
  void activeSubWindow(QMdiSubWindow *);
};

#endif  // MAINWINDOW_H
