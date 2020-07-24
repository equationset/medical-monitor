#include "qsplitterwidget.h"
#include "formwidget.h"
#include <QDebug>

QSplitterWidget::QSplitterWidget(QWidget *parent) : QWidget(parent)
{
    space = 5;
}
//窗口排列
void QSplitterWidget::arrangeWidget()
{
    int fixedSizeW = 0;
    int fixedSizeH = 0;
    int hPoint = 0;
    int wPoint = 0;
    int recordHnum  = 0;
    int recordWnum  = 0;

    for(int i = 1; i <= 30; i++){
        if(listw.size () == 1 ){
            listw.at (0)->setGeometry (space,space,this->width () - space*2,this->height () - space*2);
            listw.at (0)->show ();
            break;
        }else if(listw.size () > i*i && listw.size ()  <= (i+1)*(i+1)){
            fixedSizeW = (this->width () - space*(i+2)) / (i+1);
            fixedSizeH = (this->height () - space*(i+2)) / (i+1);
            hPoint = space;
            for(int j = 0; j < listw.size (); j++){
                hPoint = (fixedSizeH + space)*recordHnum + space;
                wPoint = (fixedSizeW + space)*recordWnum + space;
                listw.at (j)->setGeometry (wPoint,hPoint,fixedSizeW,fixedSizeH);
                listw.at (j)->show ();
                recordWnum++;
                if(recordWnum >= i+1){
                    recordWnum = 0;
                    recordHnum++;
                }
            }
            break;
        }
    }
}
//绘图
void QSplitterWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(QColor("white"));
    painter.drawRect(0,0,this->width(),this->height());
}
//大小改变
void QSplitterWidget::resizeEvent(QResizeEvent *event)
{
    arrangeWidget();
}
//添加窗口
void QSplitterWidget::addWidget(QWidget *w, int index)
{
    w->setParent (this);
    listw.insert (index,w);
    arrangeWidget();
}

void QSplitterWidget::addWidgetFirst(QWidget *w)
{
    w->setParent (this);
    listw.insert (0,w);
    arrangeWidget();
}

void QSplitterWidget::addWidgetEnd(QWidget *w)
{
    w->setParent (this);
    listw.append (w);
    arrangeWidget();
}
//删除
void QSplitterWidget::reduceWidgetFirst()
{
    if(listw.size () >= 1){
        QWidget *w =  listw.at (0);
        listw.removeAt (0);
        w->close ();
        arrangeWidget();
    }
}
//删除
void QSplitterWidget::reduceWidgetEnd()
{
    if(listw.size () >= 1){
        QWidget *w =  listw.at (listw.size ()-1);
        listw.removeAt (listw.size ()-1);
        w->close ();
        arrangeWidget();
    }
}
//删除所有
void QSplitterWidget::reduceWidgetAll()
{
    for(int i = 0; i < listw.size (); i++){
            QWidget *w =  listw.at (i);
            listw.removeAt (i);
            w->close ();
    }
    listw.clear();
}
//删除指定
void QSplitterWidget::reduceWidget(QString objectName)
{
    for(int i = 0; i < listw.size (); i++){
        if(listw.at (i)->objectName () == objectName){
            QWidget *w =  listw.at (i);
            listw.removeAt (i);
            w->close ();
            arrangeWidget();
        }
    }
}
