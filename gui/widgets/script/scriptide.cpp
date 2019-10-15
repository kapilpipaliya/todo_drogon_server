#include "./scriptide.h"
#include <QtWidgets>
#include "./editor/mainwindow.h"
#include "anglescript/script.h"
namespace widgets {
ScriptIde::ScriptIde(QWidget *parent) : QWidget(parent) { init(); }

void ScriptIde::sendmsg() { QMessageBox::information(nullptr, "hi", "hi"); }

void ScriptIde::init() {
  this->setAttribute(Qt::WA_DeleteOnClose);
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

  v1_h2->addLayout(v1_h2_v1);
  v1_h2->addLayout(v1_h2_v2);

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

void ScriptIde::initAngelScript() {
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
}  // namespace widgets
