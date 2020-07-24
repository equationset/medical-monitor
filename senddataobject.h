#ifndef SENDDATAOBJECT_H
#define SENDDATAOBJECT_H

#include <QTimer>
#include <QObject>
#include "sendserialport.h"

class SendDataObject : public QObject
{
    Q_OBJECT
public:
    explicit SendDataObject(QObject *parent = nullptr);
    ~SendDataObject();
signals:

public slots:
    void sendEcgPkg();

private:
    int ecgDataIndex;  // 索引
    SendSerialPort *com_;
    QTimer* timer;
};

#endif // SENDDATAOBJECT_H
