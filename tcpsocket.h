#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
//套接字继承QTcpSocket
class TcpSocket : public QTcpSocket
{
    Q_OBJECT

public:
    TcpSocket(QObject *parent = 0);
    ~TcpSocket();

signals:
    void disconnected(int socket);//断开连接

    void updateMsg(QByteArray ba);//数据

private slots:
    void slotDisconnected();//断开

    void slotReadData();//读取数据
};

#endif // TCPSOCKET_H
