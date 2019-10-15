#include "./mainwindow.h"
#include <QDate>
#include <QFileInfo>
#include <QLabel>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QSettings>
#include <QSignalMapper>
#include <QSortFilterProxyModel>
#include <QTime>
#include <QTimer>
#include <QtDebug>

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  this->InitForm();
  createActions();
  createMenus();
  createToolBars();
  createStatusBar();
  updateMenus();

  readSettings();

  setUnifiedTitleAndToolBarOnMac(true);
}

MainWindow::~MainWindow() {}

void MainWindow::InitForm() {
  mdiArea = new QMdiArea;
  mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  setCentralWidget(mdiArea);
  connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)), this,
          SLOT(updateMenus()));
  windowMapper = new QSignalMapper(this);
  connect(windowMapper, SIGNAL(mapped(QWidget *)), this,
          SLOT(setActiveSubWindow(QWidget *)));

  // Display date and time
  QDate dateNow = QDate::currentDate();
  dateLabel =
      new QLabel(QString("Date: %1").arg(dateNow.toString("dd/MM/yyyy dddd")));

  QTime timeNow = QTime::currentTime();
  timeLabel = new QLabel(QString("Time: %1").arg(timeNow.toString()));

  myTimer = new QTimer(this);
  myTimer->start(1000);
  connect(myTimer, SIGNAL(timeout()), this, SLOT(SetTime()));

  connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)), this,
          SLOT(activeSubWindow(QMdiSubWindow *)));
}

void MainWindow::SetTime() {
  QTime timeNow = QTime::currentTime();
  timeLabel->setText(QString("Time: %1").arg(timeNow.toString()));
}

void MainWindow::activeSubWindow(QMdiSubWindow *win) {
  if (win != nullptr) {
    QList<QMdiSubWindow *> windows = mdiArea->subWindowList();
    for (int i = 0; i < windows.size(); ++i) {
      QWidget *child = qobject_cast<QWidget *>(windows.at(i)->widget());
      //    child->setActive(false);
      // action ->setChecked(child == activeMdiChild());
    }
    QWidget *activeChild = qobject_cast<QWidget *>(win->widget());
    // activeChild->setActive(true);
  }
}

void MainWindow::closeEvent(QCloseEvent *event) {
  mdiArea->closeAllSubWindows();
  if (mdiArea->currentSubWindow()) {
    event->ignore();
  } else {
    writeSettings();
    event->accept();
  }
}

void MainWindow::about() {
  QMessageBox::about(
      this, tr("About MDI"),
      tr("The <b>MDI</b> example demonstrates how to write multiple "
         "document interface applications using Qt."));
}

void MainWindow::updateMenus() {
  bool hasMdiChild = (activeMdiChild() != nullptr);
  saveAct->setEnabled(hasMdiChild);
  closeAct->setEnabled(hasMdiChild);
  closeAllAct->setEnabled(hasMdiChild);
  tileAct->setEnabled(hasMdiChild);
  cascadeAct->setEnabled(hasMdiChild);
  nextAct->setEnabled(hasMdiChild);
  previousAct->setEnabled(hasMdiChild);
  separatorAct->setVisible(hasMdiChild);
}

void MainWindow::updateWindowMenu() {
  windowMenu->clear();
  windowMenu->addAction(closeAct);
  windowMenu->addAction(closeAllAct);
  windowMenu->addSeparator();
  windowMenu->addAction(tileAct);
  windowMenu->addAction(cascadeAct);
  windowMenu->addSeparator();
  windowMenu->addAction(nextAct);
  windowMenu->addAction(previousAct);
  windowMenu->addAction(separatorAct);

  QList<QMdiSubWindow *> windows = mdiArea->subWindowList();
  separatorAct->setVisible(!windows.isEmpty());

  for (int i = 0; i < windows.size(); ++i) {
    QWidget *child = qobject_cast<QWidget *>(windows.at(i)->widget());

    QString text;
    if (i < 9) {
      // text = tr("&%1 %2").arg(i + 1).arg(child->userFriendlyCurrentFile());
    } else {
      // text = tr("%1 %2").arg(i + 1).arg(child->userFriendlyCurrentFile());
    }
    QAction *action = windowMenu->addAction(text);
    action->setCheckable(true);
    action->setChecked(child == activeMdiChild());
    connect(action, SIGNAL(triggered()), windowMapper, SLOT(map()));
    windowMapper->setMapping(action, windows.at(i));
  }
}

void MainWindow::createActions() {
  newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
  newAct->setShortcuts(QKeySequence::New);
  newAct->setStatusTip(tr("Create a new file"));
  connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

  saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
  saveAct->setShortcuts(QKeySequence::Save);
  saveAct->setStatusTip(tr("Save the document to disk"));
  connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

  //! [0]
  exitAct = new QAction(tr("E&xit"), this);
  exitAct->setShortcuts(QKeySequence::Quit);
  exitAct->setStatusTip(tr("Exit the application"));
  connect(exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
  //! [0]

  // configAct = new QAction(QIcon(":/images/cut.png"), tr("&New"), this);
  // connect(configAct, SIGNAL(triggered()), this, SLOT(showConfigDialog()));

  closeAct = new QAction(tr("Cl&ose"), this);
  closeAct->setStatusTip(tr("Close the active window"));
  connect(closeAct, SIGNAL(triggered()), mdiArea, SLOT(closeActiveSubWindow()));

  closeAllAct = new QAction(tr("Close &All"), this);
  closeAllAct->setStatusTip(tr("Close all the windows"));
  connect(closeAllAct, SIGNAL(triggered()), mdiArea,
          SLOT(closeAllSubWindows()));

  tileAct = new QAction(tr("&Tile"), this);
  tileAct->setStatusTip(tr("Tile the windows"));
  connect(tileAct, SIGNAL(triggered()), mdiArea, SLOT(tileSubWindows()));

  cascadeAct = new QAction(tr("&Cascade"), this);
  cascadeAct->setStatusTip(tr("Cascade the windows"));
  connect(cascadeAct, SIGNAL(triggered()), mdiArea, SLOT(cascadeSubWindows()));

  nextAct = new QAction(tr("Ne&xt"), this);
  nextAct->setShortcuts(QKeySequence::NextChild);
  nextAct->setStatusTip(tr("Move the focus to the next window"));
  connect(nextAct, SIGNAL(triggered()), mdiArea, SLOT(activateNextSubWindow()));

  previousAct = new QAction(tr("Pre&vious"), this);
  previousAct->setShortcuts(QKeySequence::PreviousChild);
  previousAct->setStatusTip(
      tr("Move the focus to the previous "
         "window"));
  connect(previousAct, SIGNAL(triggered()), mdiArea,
          SLOT(activatePreviousSubWindow()));

  separatorAct = new QAction(this);
  separatorAct->setSeparator(true);

  aboutAct = new QAction(tr("&About"), this);
  aboutAct->setStatusTip(tr("Show the application's About box"));
  connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus() {
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(newAct);
  fileMenu->addAction(saveAct);
  fileMenu->addSeparator();
  QAction *action = fileMenu->addAction(tr("Switch layout direction"));
  connect(action, SIGNAL(triggered()), this, SLOT(switchLayoutDirection()));
  fileMenu->addAction(exitAct);

  windowMenu = menuBar()->addMenu(tr("&Window"));
  updateWindowMenu();
  connect(windowMenu, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));

  menuBar()->addSeparator();

  helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(aboutAct);
}

void MainWindow::createToolBars() {
  fileToolBar = new QToolBar(tr("File"), this);
  addToolBar(Qt::LeftToolBarArea, fileToolBar);
  fileToolBar->addAction(newAct);
  // fileToolBar->addAction(saveAct); //temp hide
}

void MainWindow::createStatusBar() {
  statusBar()->showMessage(tr("Ready"));

  // QGroupBox *groupBox = new QGroupBox(this);

  QDate dateNow = QDate::currentDate();
  dateLabel->setText(
      QString("Date: %1").arg(dateNow.toString("dd/MM/yyyy dddd")));

  QTime timeNow = QTime::currentTime();
  timeLabel->setText(QString("Time: %1").arg(timeNow.toString()));

  // QHBoxLayout *hbox = new QHBoxLayout;
  // hbox->addWidget(dateLabel);
  // hbox->addWidget(timeLabel);
  // groupBox->setLayout(hbox);

  statusBar()->addPermanentWidget(dateLabel);
  statusBar()->addPermanentWidget(timeLabel);
}

void MainWindow::readSettings() {
  QSettings settings("Trolltech", "MDI Example");
  QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
  QSize size = settings.value("size", QSize(400, 400)).toSize();
  move(pos);
  resize(size);
}

void MainWindow::writeSettings() {
  QSettings settings("Trolltech", "MDI Example");
  settings.setValue("pos", pos());
  settings.setValue("size", size());
}

QWidget *MainWindow::activeMdiChild() {
  if (QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow())
    return qobject_cast<QWidget *>(activeSubWindow->widget());
  return nullptr;
}

QMdiSubWindow *MainWindow::findMdiChild(const QString &fileName) {
  QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

  foreach (QMdiSubWindow *window, mdiArea->subWindowList()) {
    QWidget *mdiChild = qobject_cast<QWidget *>(window->widget());
    //    if (mdiChild->currentFile() == canonicalFilePath) return window;
  }
  return nullptr;
}

void MainWindow::switchLayoutDirection() {
  if (layoutDirection() == Qt::LeftToRight)
    qApp->setLayoutDirection(Qt::RightToLeft);
  else
    qApp->setLayoutDirection(Qt::LeftToRight);
}

void MainWindow::setActiveSubWindow(QWidget *window) {
  if (!window) return;
  mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}

void MainWindow::showStatusMessage(QString message) {
  this->statusBar()->showMessage(message, 3000);
}
