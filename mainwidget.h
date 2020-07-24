#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <qpainterwidget.h>
#include <QPushButton>
#include <QLabel>
#include <QThread>
#include <QTimer>
#include <QWidget>
#include "creatinfowidget.h"
#include "recvserialport.h"
#include "senddataobject.h"
#include "tcpobject.h"
namespace Ui {
class MainWidget;
}
//
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
protected:
    virtual void paintEvent(QPaintEvent *event);//绘图函数
signals:
    void sendStartConnect();//发送开始连接
    void sendTcpMsg(QString);//发送消息

private slots:
    void mtimeout();//定时器槽
    void on_pushButton_a_clicked();//按钮槽
    void acceptTcpMsg(QString);//接受数据
    void acceptInfo(QStringList);
private:
    Ui::MainWidget *ui;

    RecvSerialPort *m_RecvSerialPort;//发送串口
    SendDataObject *m_SendDataObject;//接受串口

    QThread workerThreadA;//线程
    QThread workerThreadB;//线程

    QTimer m_timer;//定时器

    TcpObject *m_TcpObject;//套接字
    QThread workerThread;//线程

    int recordnumtime;//时间计数
    QStringList recordstist;//列表

    CreatInfoWidget *m_CreatInfoWidget;//创建病人界面
    QStringList paintInfo;
};

#endif // MAINWIDGET_H
