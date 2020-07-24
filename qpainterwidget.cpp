#pragma execution_character_set("utf-8")
#include "qpainterwidget.h"
#include "QPainterWidget.h"
#include "qpainter.h"
#include "qmath.h"
#include "qtimer.h"
#include <QBrush>
#include "qdebug.h"
#include "smoothcurvecreator.h"

QPainterWidget::QPainterWidget(QWidget *parent) : QWidget(parent)
{
    timer = new QTimer(this);
    model = 0;
    title = "ECG II";
    timer->setInterval(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(accepttimeout()));
    maxValue = 100;
    minValue = 0;
    maxStep = 100;
    simulation_A.append(50);
    simulation_A.append(50);
    simulation_A.append(50);
    simulation_A.append(40);
    simulation_A.append(50);
    simulation_A.append(50);
    simulation_A.append(20);
    simulation_A.append(60);
    simulation_A.append(55);
    simulation_A.append(50);
    simulation_A.append(45);
    simulation_A.append(50);
    simulation_A.append(50);
    simulation_A.append(50);
    simulation_A.append(50);

    simulation_B.append(25);
    simulation_B.append(50);
    simulation_B.append(50);
    simulation_B.append(55);
    simulation_B.append(51);
    simulation_B.append(50);
    simulation_B.append(24);
    simulation_B.append(57);
    simulation_B.append(50);
    simulation_B.append(50);
    simulation_B.append(23);
    simulation_B.append(50);

    for(int i = 0;i < 20; i++){
        simulation_C.append(qrand()%10 + 45);
    }
    recordnum = 0;
}

QPainterWidget::~QPainterWidget()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

int QPainterWidget::getCurrentValue()
{
    return currentValue;
}

void QPainterWidget::setModel(int value)
{
    model = value;
}

void QPainterWidget::setTitle(QString str)
{
    title = str;
}

void QPainterWidget::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setBrush(QColor(33,33,33));
    painter.drawRect(0,0,this->width()-1,this->height()-1);

    QPen pen;
    pen.setWidth(2);
    pen.setColor("white");
    painter.setPen(pen);
    painter.drawText(30,20,title);

    if(model == 1){
        pen.setColor(QColor(34,182,42));
        painter.setPen(pen);
    }else if(model == 2){
        pen.setColor(QColor(90,35,38));
        painter.setPen(pen);
    }else if(model == 3){
        pen.setColor(QColor(111,109,86));
        painter.setPen(pen);
    }

    QPointF t_poin;
    float x_m = (float)this->width()/(float)maxStep;
    float y_m = (float)this->height()/(float)maxValue;

    knots.clear();
    for(int i = 0;i < temperature.size();i++){
        t_poin.setX((float)i*x_m);
        t_poin.setY((float)temperature.at(i)*y_m);
        knots.append(t_poin);
    }

    smoothCurve = SmoothCurveCreator::createSmoothCurve(knots);
    painter.drawPath(smoothCurve);
}

void QPainterWidget::startTimeSlot()
{
    timer->start(100);
}

void QPainterWidget::stopTimeSlot()
{
    timer->stop();
}

void QPainterWidget::accepttimeout()
{
    if(model == 1){
        recordnum++;
        if(recordnum >= simulation_A.size() - 1){
            recordnum = 0;
        }

        if(temperature.size() >= maxStep){
            temperature = temperature.mid(temperature.size()-(maxStep-1),(maxStep-1));
            currentValue = simulation_A.at(recordnum);
            temperature.append(currentValue);
        }else{
            currentValue = simulation_A.at(recordnum);
            temperature.append(currentValue);
        }
        emit sendCurrentValue(QString::number(simulation_A.at(recordnum)));
    }

    if(model == 2){
        recordnum++;
        if(recordnum >= simulation_B.size() - 1){
            recordnum = 0;
        }

        if(temperature.size() >= maxStep){
            temperature = temperature.mid(temperature.size()-(maxStep-1),(maxStep-1));
            currentValue = simulation_B.at(recordnum);
            temperature.append(currentValue);
        }else{
            currentValue = simulation_B.at(recordnum);
            temperature.append(currentValue);
        }
        emit sendCurrentValue(QString::number(simulation_B.at(recordnum)));
    }

    if(model == 3){
        recordnum++;
        if(recordnum >= simulation_C.size() - 1){
            recordnum = 0;
        }

        if(temperature.size() >= maxStep){
            temperature = temperature.mid(temperature.size()-(maxStep-1),(maxStep-1));
            currentValue = simulation_C.at(recordnum);
            temperature.append(currentValue);
        }else{
            currentValue = simulation_C.at(recordnum);
            temperature.append(currentValue);
        }
        emit sendCurrentValue(QString::number(simulation_C.at(recordnum)));
    }

    update();
}

void QPainterWidget::setCurrentTemp(int value)
{
    if(temperature.size() >= maxStep){
        temperature = temperature.mid(temperature.size()-(maxStep-1),(maxStep-1));
        temperature.append(value);
    }else{
        temperature.append(value);
    }
    update();
}
