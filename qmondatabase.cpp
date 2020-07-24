#pragma execution_character_set("utf-8")
#include "qmondatabase.h"
#include <QDebug>
#define DATA_BASE_NAME ("QMonitorSys.db")//数据库文件名
QSqlDatabase QMonDataBase::database;

QMonDataBase::QMonDataBase(QObject *parent) : QObject(parent)
{
    if (QSqlDatabase::contains(DATA_BASE_NAME)) {//连接数据库
          database = QSqlDatabase::database(DATA_BASE_NAME);
      } else {
          database = QSqlDatabase::addDatabase("QSQLITE",DATA_BASE_NAME);//QSQLITE改成QMYSQL
      }
      database.setDatabaseName(DATA_BASE_NAME);//设置数据库文件名
      database.setUserName("root");//用户
      database.setPassword("nopassword");//密码-无密码

      if (!database.open()){//打开数据库
          qCritical() << database.lastError().text();
          return;
      }

      QSqlQuery query(database);
      //管理员用户
      bool ret = 0;
      ret = query.exec(QString::fromLocal8Bit("create table patient_information(id varchar(50) primary key,name varchar(20),phone varchar(10),sex varchar(20),age varchar(20))"));
      query.exec(QString::fromLocal8Bit("insert into patient_information values('50011112523565645','158260454545','赵四','男','33')"));

      database.close();
      qDebug()<<"ddddddddd"<<ret;
}

QMonDataBase::~QMonDataBase()
{

}
//
QVector<QVector<QString> > QMonDataBase::queryAll(QString tablename)
{
    if (! QMonDataBase::database.open()){//打开数据库
           qCritical() << QMonDataBase::database.lastError().text();
       }
       QSqlQuery query(QMonDataBase::database);
       QString statement = QString("SELECT * FROM %1").arg(tablename);
       query.exec(statement);
       QVector<QVector<QString>> retvector;
       QVector<QString> vectorstr;
       int midsize = 0;
       while(query.next())
       {
           vectorstr.clear();
           midsize = query.size();
           for(int i = 0; i < 40;i++ ){
               vectorstr.append(query.value(i).toByteArray());
           }
           retvector.append(vectorstr);
       }
       QMonDataBase::database.close();
       return retvector;
}
