#include "formwidget.h"
#include "ui_formwidget.h"
#include <QPalette>
#include <QPainter>
#include "detectionwidget.h"

FormWidget::FormWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormWidget)
{
    ui->setupUi(this);
    m_DetectionWidget = new DetectionWidget();
    connect(this,SIGNAL(sendMSG(QByteArray)),m_DetectionWidget,SLOT(setMSG(QByteArray)));
    m_DetectionWidget->hide();
}

FormWidget::~FormWidget()
{
    delete m_DetectionWidget;
    delete ui;
}
//绘图
void FormWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(QColor(33,33,33));
    painter.drawRect(0,0,this->width(),this->height());

    int t_w = this->width();
    int t_h = this->height();
    QStringList strlist = QString(msgstr).split(":");
//绘制数据
    if(strlist.size()>=4&&dev_id == strlist.at(1)){
        painter.drawText(t_w*0.4,t_h*0.3,QString("PORT:%1").arg(strlist.at(1)));
        painter.drawText(t_w*0.4,t_h*0.4,QString("ECG:%1").arg(strlist.at(3)));
        painter.drawText(t_w*0.4,t_h*0.5,QString("SPO2:%1").arg(strlist.at(4)));
        painter.drawText(t_w*0.4,t_h*0.6,QString("RESP:%1").arg(strlist.at(5)));
    }

}
//鼠标双击
void FormWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    m_DetectionWidget->show();
}
//设备id
void FormWidget::setDevID(QString str)
{
    m_DetectionWidget->setDevID(str);
    dev_id = str;
}
//发送数据
void FormWidget::setMSG(QByteArray datagram)
{
    QStringList strlist = QString(datagram).split(":");

    if(strlist.size()>=4&&dev_id == strlist.at(1)){
        msgstr = datagram;
        emit sendMSG(datagram);
        update();
    }
}


