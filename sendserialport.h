#ifndef SENDSERIALPORT_H
#define SENDSERIALPORT_H

#include <QSerialPort>
#include <QObject>
class SendSerialPort : public QSerialPort
{
    Q_OBJECT
public:
    explicit SendSerialPort(QObject *parent = nullptr);

    void sendMessage(char buff[], int len);
public slots:
    void readMessage();
signals:
    void sigDealMessage();
};

#endif // SENDSERIALPORT_H
