#ifndef TCPOBJECT_H
#define TCPOBJECT_H

#include <QObject>
#include <QtNetwork>
//套接字对象
class TcpObject : public QObject
{
    Q_OBJECT
public:
    explicit TcpObject(QObject *parent = nullptr);

signals:
    void sendTcpMsg(QString);//发送数据
public slots:
    void ReadError(QAbstractSocket::SocketError);//错误
    void readData();//读取数据
    void mtimeout();//定时器槽
    void connectTcp();//连接
    void startConnect();//开始连接
    void acceptTcpMsg(QString);//接受数据
private:
    QTcpSocket * tcpClient;//套接字
    bool connectState;//连接状态
    QTimer *timer;//定时器
};

#endif // TCPOBJECT_H
