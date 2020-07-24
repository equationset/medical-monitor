#ifndef QMONDATABASE_H
#define QMONDATABASE_H
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QObject>

class QMonDataBase : public QObject
{
    Q_OBJECT
public:
    explicit QMonDataBase(QObject *parent = nullptr);
    ~QMonDataBase();

    static QVector<QVector<QString>> queryAll(QString tablename);//查询所有

public:
    static  QSqlDatabase database;//数据库
};

#endif // QMONDATABASE_H
