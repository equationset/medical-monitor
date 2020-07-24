#ifndef TCPSERVERWIDGET_H
#define TCPSERVERWIDGET_H

#include <QWidget>
#include <QThread>
#include <QTcpServer>
#include <QMessageBox>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDateTime>
#include "server.h"
#include <QTimer>
#include <QDateTime>
#include "formwidget.h"

namespace Ui {
class TcpServerWidget;
}
//主界面
class TcpServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TcpServerWidget(QWidget *parent = 0);
    ~TcpServerWidget();


signals:
    void sendMSG(QString);//发送信息
    void sendConfig(QString ,int);//发送配置

private slots:
    void slotUpdate(QByteArray datagram);//接收数据
    void mtimeout();//定时器

    void acceptConnect(QStringList);//连接列表



private:
    Ui::TcpServerWidget *ui;
    QThread workThread;//线程
    Server *server;//服务器
    QTimer timer;//定时器
    bool timestate;//状态
    QList<FormWidget*> listw;//界面的列表
};

#endif // TCPSERVERWIDGET_H
