#ifndef DGRAPHLOG_H
#define DGRAPHLOG_H

#include <QWidget>
#include <QtWidgets>
namespace widgets {
class DGraphLog : public QWidget
{
    Q_OBJECT
public:
    explicit DGraphLog(QWidget *parent = nullptr);
    void addSendLog(const std::string &s);
    void addReceiveLog(const std::string &s);


signals:

public slots:

private:
    void init();
    int eventno=0;
    QVBoxLayout *sendlog_vbox;
    QVBoxLayout *receivelog_vbox ;

};
extern DGraphLog *dgraphlog;
}
#endif // DGRAPHLOG_H
