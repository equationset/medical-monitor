#pragma execution_character_set("utf-8")
#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QPainter>
#include <QDateTime>
#include "qmondatabase.h"


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    QMonDataBase db;//数据库创建
    ui->setupUi(this);

    setWindowTitle("检测仪");
    setFixedSize(816,437);
    m_CreatInfoWidget = new CreatInfoWidget;
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(mtimeout()));
    m_timer.start(100);
    recordnumtime = 0;
    ui->widget_a->setModel(1);
    ui->widget_b->setModel(2);
    ui->widget_c->setModel(3);

    ui->widget_a->setTitle("ECG II      x1");
    ui->widget_b->setTitle("SPO2");
    ui->widget_c->setTitle("RESP       x1");

    ui->widget_a->startTimeSlot();
    ui->widget_b->startTimeSlot();
    ui->widget_c->startTimeSlot();
    
    m_RecvSerialPort = new RecvSerialPort;
    m_SendDataObject = new SendDataObject;
    //移动到线程
    m_RecvSerialPort->moveToThread(&workerThreadA);
    m_SendDataObject->moveToThread(&workerThreadB);
    //连接信号槽
    connect(&workerThreadA, &QThread::finished, m_RecvSerialPort, &QObject::deleteLater);
    connect(&workerThreadB, &QThread::finished, m_SendDataObject, &QObject::deleteLater);

    workerThreadA.start();
    workerThreadB.start();

    m_TcpObject = new TcpObject;
    m_TcpObject->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, m_TcpObject, &QObject::deleteLater);
    workerThread.start();
    connect(this,SIGNAL(sendStartConnect()),m_TcpObject,SLOT(startConnect()));
    connect(m_TcpObject,SIGNAL(sendTcpMsg(QString)),this,SLOT(acceptTcpMsg(QString)));
    connect(this,SIGNAL(sendTcpMsg(QString)),m_TcpObject,SLOT(acceptTcpMsg(QString)));

    emit sendStartConnect();//开始连接

    //添加默认数据
    paintInfo.append("id");
    paintInfo.append("name");
    paintInfo.append("phone");
    paintInfo.append("sex");
    paintInfo.append("age");
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

        ui->label_id->setText(QString("xd 00%1").arg(qrand()%5+10));
}
//退出
MainWidget::~MainWidget()
{
    workerThreadA.quit();
    workerThreadA.wait();
    workerThreadB.quit();
    workerThreadB.wait();
    delete m_RecvSerialPort;
    delete m_SendDataObject;
    delete ui;
}
//绘图
void MainWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(QColor(48,48,48));
    painter.drawRect(0,0,this->width(),this->height());
}
//定时器槽
void MainWidget::mtimeout()
{
    QStringList stist;
    //添加数据
    stist.append(QString::number(ui->widget_a->getCurrentValue()));
    stist.append(QString::number(ui->widget_b->getCurrentValue()));
    stist.append(QString::number(ui->widget_c->getCurrentValue()));

    //发送数据
    recordnumtime++;
    if(recordnumtime >= 10){
        ui->label_A_1->setText(QString::number(ui->widget_a->getCurrentValue()));
        ui->label_B_1->setText(QString::number(ui->widget_b->getCurrentValue()));
        ui->label_D_1->setText(QString::number(ui->widget_c->getCurrentValue()));
        recordnumtime = 0;
        recordstist.clear();
        int randnum = qrand()%10 + 40;//随机数据
        recordstist.append(QString::number(randnum));
        ui->label_A_2->setText(QString::number(randnum));
        randnum = qrand()%10 + 60;//随机数据
        recordstist.append(QString::number(randnum));
        ui->label_A_3->setText(QString::number(randnum));
        randnum = qrand()%10 + 50;//随机数据
        recordstist.append(QString::number(randnum));
        ui->label_A_4->setText(QString::number(randnum));

        randnum = qrand()%10 + 30;//随机数据
        recordstist.append(QString::number(randnum));
        ui->label_B_2->setText(QString::number(randnum));
        randnum = qrand()%10 + 70;
        recordstist.append(QString::number(randnum));
        ui->label_B_3->setText(QString::number(randnum));

        randnum = qrand()%10 + 70;
        recordstist.append(QString::number(randnum));
        ui->label_C_2->setText(QString::number(randnum));
        randnum = qrand()%10 + 30;
        recordstist.append(QString::number(randnum));
        ui->label_C_3->setText(QString::number(randnum));
        randnum = qrand()%10 + 50;
        recordstist.append(QString::number(randnum));
        ui->label_C_4->setText(QString::number(randnum));

        randnum = qrand()%10 + 60;//随机数据
        recordstist.append(QString::number(randnum));
        ui->label_D_2->setText(QString::number(randnum));
        randnum = qrand()%10 + 110;//随机数据
        recordstist.append(QString::number(randnum));
        ui->label_D_3->setText(QString::number(randnum));
        randnum = qrand()%10 + 100;//随机数据
        recordstist.append(QString::number(randnum));
        ui->label_D_4->setText(QString::number(randnum));
    }
    stist.append(recordstist);//添加界面数据

    QString sendstr;
    sendstr+="MSG";
    for(int i = 0;i < stist.size();i++){
        sendstr+=":";
        sendstr+=stist.at(i);
    }
    sendstr+=":";
    sendstr+=ui->label_id->text();

    //病人信息追加到最后
    sendstr+=":";
    sendstr+=paintInfo.at(0);
    sendstr+=":";
    sendstr+=paintInfo.at(1);
    sendstr+=":";
    sendstr+=paintInfo.at(2);
    sendstr+=":";
    sendstr+=paintInfo.at(3);
    sendstr+=":";
    sendstr+=paintInfo.at(4);

    emit sendTcpMsg(sendstr);//发送出去
}

void MainWidget::on_pushButton_a_clicked()
{
    //显示病人界面
    m_CreatInfoWidget->show();
}
//接受数据
void MainWidget::acceptTcpMsg(QString str)
{
    QStringList strlist = str.split(":");

    if(strlist.at(0) == "FLAG"){
    }
}

void MainWidget::acceptInfo(QStringList plist)
{
    paintInfo.clear();
    paintInfo.append(plist);
}
