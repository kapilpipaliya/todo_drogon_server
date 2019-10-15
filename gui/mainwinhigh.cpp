#include "./mainwinhigh.h"
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QToolBar>

#include "widgets/dgraphlog/dgraphlog.h"
#include "widgets/script/scriptide.h"

#include "./logmanager.h"
MainWinHigh::MainWinHigh(QWidget *parent) : MainWindow(parent) {
  setWindowTitle(tr("Generator Software"));

  //    M_DB dbConnection = M_DB(0);
  //    QPixmap p1 = dbConnection.getImage();
  // QPixmap p2 = p1.scaled(500, 500, Qt::KeepAspectRatio); // on constructor we
  // not have proper size of label.
  //    this->setWindowIcon(p1);

  auto newToolBar = new QToolBar(this);
  addToolBar(Qt::TopToolBarArea, newToolBar);

  auto scriptAction = new QAction("script", this);
  newToolBar->addAction(scriptAction);
  connect(scriptAction, &QAction::triggered, [this]() {
    auto child = new widgets::ScriptIde;
    addMdiChild(child);
    child->show();
  });

  auto dgraphlogAction = new QAction("dgraphlog", this);
  newToolBar->addAction(dgraphlogAction);
  auto addlogmdi = [this]() {
    auto child = new widgets::DGraphLog;
    addMdiChild(child);
    child->show();
  };
  connect(dgraphlogAction, &QAction::triggered, addlogmdi);
  addlogmdi();
}

void MainWinHigh::adminLoggedIn() {
  this->show();
  configToolBar = new QToolBar(tr("config"), this);
  addToolBar(Qt::LeftToolBarArea, configToolBar);
  // fileToolBar->addAction(configAct);
}

void MainWinHigh::userLoggedIn() { this->show(); }

void MainWinHigh::showConfigDialog() {
  //  confDialog = new ConfDialog(this);
  //  confDialog->show();
}

QWidget *MainWinHigh::createMdiChild() {
  /*auto child = new widgets::ModelWriter(this);
  QMdiSubWindow *subWindow = mdiArea->addSubWindow(child);
  subWindow->setWindowIcon(QIcon(":/images/copy.png"));
  subWindow->resize(1100, 800);
  return child;*/
}
void MainWinHigh::addMdiChild(QWidget *child) {
  QMdiSubWindow *subWindow = mdiArea->addSubWindow(child);
  subWindow->setWindowIcon(QIcon(":/images/copy.png"));
  subWindow->resize(1100, 800);
}

void MainWinHigh::newFile() {
  QWidget *child = createMdiChild();
  child->show();
}

/*
void MainWinHigh::open()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
        QMdiSubWindow *existing = findMdiChild(fileName);
        if (existing) {
            mdiArea->setActiveSubWindow(existing);
            return;
        }

        QWidget *child = createMdiChild();
        if (child->loadFile(fileName)) {
            statusBar()->showMessage(tr("File loaded"), 2000);
            child->show();
        } else {
            child->close();
        }
    }
}
*/
void MainWinHigh::save() {
  //  if (activeMdiChild() && activeMdiChild()->save())
  //    statusBar()->showMessage(tr("File saved"), 2000);
}
