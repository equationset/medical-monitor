#pragma execution_character_set("utf-8")
#include "server.h"
#include <QDebug>

Server::Server(QObject *parent, quint16 port) : QTcpServer(parent)
{

}

Server::~Server()
{

}
//发送数据
void Server::sendMSG(QString buf)
{
    foreach (TcpSocket *c, clients) {
        c->write(buf.toLatin1());
    }
}
//监听
void Server::acceptConfig(QString ip, int port)
{
    bool ret = listen(QHostAddress(ip), port);
    if(ret == true){
        qDebug()<<"listen ok";
    }
    connect(this, SIGNAL(newConnection()), SLOT(slotAccept()));
}
//新连接
void Server::slotAccept()
{  
    qDebug() << "newConnection";
}

void Server::slotReadData()
{
    qDebug()<<"";
}
//连接
void Server::incomingConnection(qintptr socket)
{
    qDebug() << "incomingConnection";
    client = new TcpSocket();
    client->setSocketDescriptor(socket);

    connect(client, SIGNAL(readyRead()),this, SLOT(slotReadData()));
    connect(client, SIGNAL(disconnected(int)),
            this, SLOT(slotDisconnected(int)));
    connect(client, SIGNAL(updateMsg(QByteArray)),
            this, SLOT(slotUpdate(QByteArray)));

    clients << client;


    QStringList strlist;
    foreach (TcpSocket *c, clients) {
        strlist.append(QString::number(c->socketDescriptor()));
    }
    emit sendConnect(strlist);
}
//断开
void Server::slotDisconnected(int socketDescrip)
{
    qDebug() << "disconnect client : " << socketDescrip;
    foreach (TcpSocket *c, clients) {
        if(c->socketDescriptor() == socketDescrip)
            clients.removeOne(c);
        break;
    }
    QStringList strlist;
    foreach (TcpSocket *c, clients) {
        strlist.append(QString::number(c->socketDescriptor()));
    }
    emit sendConnect(strlist);
    return;
}
//数据接收
void Server::slotUpdate(QByteArray datagram)
{
    emit updateMsg(datagram);

    //    foreach (TcpSocket *c, clients) {
    //        c->write(datagram);
    //    }

}
