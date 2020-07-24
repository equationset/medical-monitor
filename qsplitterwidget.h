#ifndef QSPLITTERWIDGET_H
#define QSPLITTERWIDGET_H

#include <QWidget>
#include <QList>
#include <QWidget>
#include <QPainter>
//窗口分割控件
class QSplitterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QSplitterWidget(QWidget *parent = 0);

protected:
    void arrangeWidget();//排列窗口
    virtual void paintEvent(QPaintEvent *event);//绘图
    virtual void resizeEvent(QResizeEvent *event);//大小改变事件
signals:

public:
    void addWidget(QWidget* w,int index);//添加窗口
    void addWidgetFirst(QWidget* w);//头部添加
    void addWidgetEnd(QWidget* w);//尾部添加
    void reduceWidgetFirst();//删除头窗口
    void reduceWidgetEnd();//删除尾部
    void reduceWidgetAll();//删除所有
    void reduceWidget(QString objectName);//删除指定
private:
    QList<QWidget*> listw;//窗口列表的指针
    int space;//间隔
};

#endif // QSPLITTERWIDGET_H
