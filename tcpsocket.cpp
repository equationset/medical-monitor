#pragma execution_character_set("utf-8")
#include "tcpsocket.h"

TcpSocket::TcpSocket(QObject *parent):QTcpSocket(parent)
{
    connect(this, SIGNAL(disconnected()), SLOT(slotDisconnected()));
    connect(this, SIGNAL(readyRead()), SLOT(slotReadData()));
}

TcpSocket::~TcpSocket()
{

}

void TcpSocket::slotDisconnected()
{
    emit disconnected(socketDescriptor());
}
//读取数据
void TcpSocket::slotReadData()
{
    while(bytesAvailable() > 0){
        QByteArray datagrame;
        datagrame.resize(bytesAvailable());
        read(datagrame.data(), datagrame.size());
        emit updateMsg("PORT:" + QString::number((int)socketDescriptor()).toLatin1() + ":" + datagrame);
    }
}
