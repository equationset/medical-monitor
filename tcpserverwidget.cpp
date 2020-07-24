#pragma execution_character_set("utf-8")
#include "tcpserverwidget.h"
#include "ui_tcpserverwidget.h"
#include "formwidget.h"

TcpServerWidget::TcpServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpServerWidget)
{
    ui->setupUi(this);
    setWindowTitle("医生工作站");
    server = new Server();
    timestate = false;
    //连接信号槽
    connect(server, SIGNAL(updateMsg(QByteArray)),
            this, SLOT(slotUpdate(QByteArray)));
    connect(&workThread, &QThread::finished, server, &QObject::deleteLater);
    connect(this, SIGNAL(sendMSG(QString)),server, SLOT(sendMSG(QString)));
    connect(this, SIGNAL(sendConfig(QString ,int)),server, SLOT(acceptConfig(QString ,int)));
    connect(server, SIGNAL(sendConnect(QStringList)),this, SLOT(acceptConnect(QStringList)));

    server->moveToThread(&workThread);

    workThread.start();//线程开始

    connect(&timer,SIGNAL(timeout()),this,SLOT(mtimeout()));

    timer.start(500);

//发送配置
    emit sendConfig("127.0.0.1",520);


}

TcpServerWidget::~TcpServerWidget()
{
    workThread.quit();
    workThread.wait();
    delete ui;
}
//接受的数据
void TcpServerWidget::slotUpdate(QByteArray datagram)
{
    QString buf(datagram);
    qDebug()<<"slotUpdate"<<buf;

    for(int i = 0;i < listw.size();i++){
        FormWidget *w = listw.at(i);
        w->setMSG(datagram);
    }
}
//定时器槽函数
void TcpServerWidget::mtimeout()
{


}
//接收有哪些连接
void TcpServerWidget::acceptConnect(QStringList strlst)
{
    ui->splitterWidget->reduceWidgetAll();
    for(int i = 0;i < strlst.size();i++){
        FormWidget *w = new FormWidget();
        listw.append(w);
        w->setDevID(strlst.at(i));
        ui->splitterWidget->addWidgetEnd(w);
    }
}
