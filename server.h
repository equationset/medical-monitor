#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QDebug>
#include <QHostAddress>
#include <QTcpSocket>
#include "tcpsocket.h"
//服务器
class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent = 0, quint16 port = 520);
    ~Server();

signals:
    void updateMsg(QByteArray datagram);//转发数据信号
    void sendConnect(QStringList);//发送连接

public slots:
    void sendMSG(QString);//槽
    void acceptConfig(QString ,int);//配置

private slots:
    void slotAccept();//连接
    void slotReadData();//读取数据
    void slotDisconnected(int socketDescrip);//断开连接
    void slotUpdate(QByteArray datagram);//刷新

protected:
    virtual void incomingConnection(qintptr socket);//虚函数

private:
    QList<TcpSocket *> clients;//套接字列表
    TcpSocket *client;//指针

};

#endif // SERVER_H
