// Todo add button to clear log too.
// Todo add button to add retal web client

#include "./dgraphlog.h"
namespace widgets {
DGraphLog *dgraphlog = nullptr;
DGraphLog::DGraphLog(QWidget *parent) : QWidget(parent) {
  init();
  dgraphlog = this;
}

void DGraphLog::addSendLog(const std::string &s) {
  auto h = new QHBoxLayout();

  auto spinbox = new QSpinBox(this);
  auto log = new QPlainTextEdit(this);
  spinbox->setValue(eventno);
  eventno++;
  log->setPlainText(QString::fromStdString(s));

  h->addWidget(spinbox);
  h->addWidget(log);
  sendlog_vbox->addItem(h);
}

void DGraphLog::addReceiveLog(const std::string &s) {
  auto h = new QHBoxLayout();

  auto spinbox = new QSpinBox(this);
  auto log = new QPlainTextEdit(this);
  spinbox->setValue(eventno);
  eventno++;
  log->setPlainText(QString::fromStdString(s));

  h->addWidget(spinbox);
  h->addWidget(log);
  receivelog_vbox->addItem(h);
}

void DGraphLog::init() {
  this->setAttribute(Qt::WA_DeleteOnClose);
  auto v1 = new QVBoxLayout(this);

  auto v1_h1 = new QHBoxLayout();

  auto v1_h1_v1 = new QVBoxLayout();
  auto v1_h1_v2 = new QVBoxLayout();

  v1_h1->addLayout(v1_h1_v1);
  v1_h1->addLayout(v1_h1_v2);

  auto scrollview = new QScrollArea(this);
  auto scrolllayout = new QHBoxLayout(scrollview);
  sendlog_vbox = new QVBoxLayout();
  receivelog_vbox = new QVBoxLayout();
  scrolllayout->addLayout(sendlog_vbox);
  scrolllayout->addLayout(receivelog_vbox);
  v1_h1_v2->addWidget(scrollview);

  v1->addItem(v1_h1);

  v1_h1->setStretch(1, 2);
  this->setLayout(v1);
}
}  // namespace widgets
