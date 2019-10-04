#include "mainhighscriptide.h"
#include <QtWidgets>
#include "./editor/mainwindow.h"
#include "anglescript/script.h"
MainHighScriptIDe::MainHighScriptIDe(QWidget *parent) : QWidget(parent) {
  init();
}

void MainHighScriptIDe::init() {
  initAngelScript();
  auto v1 = new QVBoxLayout(this);

  auto v1_h1 = new QHBoxLayout();

  auto v1_h1_v1 = new QVBoxLayout();
  auto v1_h1_v2 = new QVBoxLayout();

  v1_h1->addLayout(v1_h1_v1);
  v1_h1->addLayout(v1_h1_v2);

  auto v1_h2 = new QHBoxLayout();

  auto v1_h2_v1 = new QVBoxLayout();
  auto v1_h2_v2 = new QVBoxLayout();

  v1_h1->addLayout(v1_h2_v1);
  v1_h1->addLayout(v1_h2_v2);

  v1->addItem(v1_h1);
  v1->addItem(v1_h2);

  // add dir tree to v1_h1_v1
  QString rootPath = QDir::current().path();
  auto model = new QFileSystemModel();
  model->setRootPath("");
  auto tree = new QTreeView(this);
  tree->setModel(model);
  if (!rootPath.isEmpty()) {
    const QModelIndex rootIndex = model->index(QDir::cleanPath(rootPath));
    if (rootIndex.isValid()) tree->setRootIndex(rootIndex);
  }

  // Demonstrating look and feel features
  tree->setAnimated(false);
  tree->setIndentation(20);
  tree->setSortingEnabled(true);
  const QSize availableSize =
      QApplication::desktop()->availableGeometry(tree).size();
  tree->resize(availableSize / 2);
  tree->setColumnWidth(0, tree->width() / 3);
  v1_h1_v1->addWidget(tree);

  // add tabwidget to v1_h1_v2
  auto tabWidget1 = new QTabWidget(this);
  tabWidget1->setTabsClosable(true);
  QString fileName;
  QFileInfo fileInfo(fileName);
  tabWidget1->addTab(new GeneralTab(fileInfo), tr("General"));
  tabWidget1->addTab(new PermissionsTab(fileInfo), tr("Permissions"));
  tabWidget1->addTab(new ApplicationsTab(fileInfo), tr("Applications"));
  v1_h1_v2->addWidget(tabWidget1);

  v1_h1->setStretch(1, 2);
  this->setLayout(v1);

  // connect dirtree with tabbar

  connect(tree, &QTreeView::clicked,
          [this, tabWidget1, model](const QModelIndex &index) {
            //    QMessageBox::information(nullptr, "hi", "hi");
            auto editor = new widgets::scripter::MainWindow();
            // auto file = index.data().toString();
            auto file = model->filePath(index);
            editor->loadFile(file);
            editor->setWindowFlags(Qt::Widget);
            editor->show();
            auto i = tabWidget1->addTab(editor, index.data().toString());
            tabWidget1->setCurrentIndex(i);
            connect(editor, &widgets::scripter::MainWindow::runScript,
                    [this](QString filename) {
                      auto r = script->CompileScript(filename.toStdString());
                      if (r) {
                        script->Execute("");
                      }
                    });
          });
  connect(tabWidget1, &QTabWidget::tabCloseRequested, [tabWidget1](int index) {
    tabWidget1->widget(index)->deleteLater();
    tabWidget1->removeTab(index);
  });
}

void MainHighScriptIDe::initAngelScript() {
  //---------angelscript
  // Create the script engine
  script = new Script;
  // Compile the script code
  auto r = script->CompileScript("");
  if (r) {
    // execute
    script->Execute("");
  }
}

//! [6]
GeneralTab::GeneralTab(const QFileInfo &fileInfo, QWidget *parent)
    : QWidget(parent) {
  QLabel *fileNameLabel = new QLabel(tr("File Name:"));
  QLineEdit *fileNameEdit = new QLineEdit(fileInfo.fileName());

  QLabel *pathLabel = new QLabel(tr("Path:"));
  QLabel *pathValueLabel = new QLabel(fileInfo.absoluteFilePath());
  pathValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

  QLabel *sizeLabel = new QLabel(tr("Size:"));
  qlonglong size = fileInfo.size() / 1024;
  QLabel *sizeValueLabel = new QLabel(tr("%1 K").arg(size));
  sizeValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

  QLabel *lastReadLabel = new QLabel(tr("Last Read:"));
  QLabel *lastReadValueLabel = new QLabel(fileInfo.lastRead().toString());
  lastReadValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

  QLabel *lastModLabel = new QLabel(tr("Last Modified:"));
  QLabel *lastModValueLabel = new QLabel(fileInfo.lastModified().toString());
  lastModValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(fileNameLabel);
  mainLayout->addWidget(fileNameEdit);
  mainLayout->addWidget(pathLabel);
  mainLayout->addWidget(pathValueLabel);
  mainLayout->addWidget(sizeLabel);
  mainLayout->addWidget(sizeValueLabel);
  mainLayout->addWidget(lastReadLabel);
  mainLayout->addWidget(lastReadValueLabel);
  mainLayout->addWidget(lastModLabel);
  mainLayout->addWidget(lastModValueLabel);
  mainLayout->addStretch(1);
  setLayout(mainLayout);
}
//! [6]

//! [7]
PermissionsTab::PermissionsTab(const QFileInfo &fileInfo, QWidget *parent)
    : QWidget(parent) {
  QGroupBox *permissionsGroup = new QGroupBox(tr("Permissions"));

  QCheckBox *readable = new QCheckBox(tr("Readable"));
  if (fileInfo.isReadable()) readable->setChecked(true);

  QCheckBox *writable = new QCheckBox(tr("Writable"));
  if (fileInfo.isWritable()) writable->setChecked(true);

  QCheckBox *executable = new QCheckBox(tr("Executable"));
  if (fileInfo.isExecutable()) executable->setChecked(true);

  QGroupBox *ownerGroup = new QGroupBox(tr("Ownership"));

  QLabel *ownerLabel = new QLabel(tr("Owner"));
  QLabel *ownerValueLabel = new QLabel(fileInfo.owner());
  ownerValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

  QLabel *groupLabel = new QLabel(tr("Group"));
  QLabel *groupValueLabel = new QLabel(fileInfo.group());
  groupValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

  QVBoxLayout *permissionsLayout = new QVBoxLayout;
  permissionsLayout->addWidget(readable);
  permissionsLayout->addWidget(writable);
  permissionsLayout->addWidget(executable);
  permissionsGroup->setLayout(permissionsLayout);

  QVBoxLayout *ownerLayout = new QVBoxLayout;
  ownerLayout->addWidget(ownerLabel);
  ownerLayout->addWidget(ownerValueLabel);
  ownerLayout->addWidget(groupLabel);
  ownerLayout->addWidget(groupValueLabel);
  ownerGroup->setLayout(ownerLayout);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(permissionsGroup);
  mainLayout->addWidget(ownerGroup);
  mainLayout->addStretch(1);
  setLayout(mainLayout);
}
//! [7]

//! [8]
ApplicationsTab::ApplicationsTab(const QFileInfo &fileInfo, QWidget *parent)
    : QWidget(parent) {
  QLabel *topLabel = new QLabel(tr("Open with:"));

  QListWidget *applicationsListBox = new QListWidget;
  QStringList applications;

  for (int i = 1; i <= 30; ++i)
    applications.append(tr("Application %1").arg(i));
  applicationsListBox->insertItems(0, applications);

  QCheckBox *alwaysCheckBox;

  if (fileInfo.suffix().isEmpty())
    alwaysCheckBox =
        new QCheckBox(tr("Always use this application to "
                         "open this type of file"));
  else
    alwaysCheckBox = new QCheckBox(tr("Always use this application to "
                                      "open files with the extension '%1'")
                                       .arg(fileInfo.suffix()));

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(topLabel);
  layout->addWidget(applicationsListBox);
  layout->addWidget(alwaysCheckBox);
  setLayout(layout);
}
