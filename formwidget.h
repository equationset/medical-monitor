#ifndef FORMWIDGET_H
#define FORMWIDGET_H

#include <QWidget>
#include "detectionwidget.h"

namespace Ui {
class FormWidget;
}
//界面窗口
class FormWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FormWidget(QWidget *parent = 0);
    ~FormWidget();
protected:
    virtual void paintEvent(QPaintEvent *event);//绘图
    virtual void mouseDoubleClickEvent(QMouseEvent *event);//鼠标双击事件

signals:
    void sendMSG(QByteArray);//发生数据
public slots:
    void setDevID(QString);//设备
    void setMSG(QByteArray);//消息

private:
    Ui::FormWidget *ui;
    QString dev_id;//设备
    DetectionWidget *m_DetectionWidget;//弹出界面
    QByteArray msgstr;//数据

};

#endif // FORMWIDGET_H
