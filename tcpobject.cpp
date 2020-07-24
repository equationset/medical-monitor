#pragma execution_character_set("utf-8")
#include "tcpobject.h"
#include <QDebug>

TcpObject::TcpObject(QObject *parent) : QObject(parent)
{
    tcpClient = new QTcpSocket(this);
    connectState = false;
    tcpClient->abort();
    //连接
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(readData()));
    connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(ReadError(QAbstractSocket::SocketError)));
}
//错误或者断开
void TcpObject::ReadError(QAbstractSocket::SocketError)
{
    connectState = false;
    tcpClient->disconnectFromHost();
}
//读取数据
void TcpObject::readData()
{
    QString buf =  tcpClient->readAll();//这里是客户端收到的值
    emit sendTcpMsg(buf);
}
//定时器槽
void TcpObject::mtimeout()
{
    qDebug()<<"connectState"<<connectState;
    if(connectState == false){
        connectTcp();
    }
}
//连接
void TcpObject::connectTcp()
{
    tcpClient->connectToHost("127.0.0.1",520);
    if (tcpClient->waitForConnected(1000))
    {
        connectState = true;
    }
}
//开开始连接
void TcpObject::startConnect()
{
    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(mtimeout()));
    timer->start(500);
}
//接收数据
void TcpObject::acceptTcpMsg(QString str)
{
     qDebug()<<"str"<<str;
    tcpClient->write(str.toLatin1());
}
