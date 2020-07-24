#pragma execution_character_set("utf-8")
#include "detectionwidget.h"
#include "ui_detectionwidget.h"
#include "creatinfowidget.h"

DetectionWidget::DetectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetectionWidget)
{
    ui->setupUi(this);
    setWindowTitle("监测数据");
    //设置模式
    ui->widget_a->setModel(1);
    ui->widget_b->setModel(2);
    ui->widget_c->setModel(3);
    //设置标题
    ui->widget_a->setTitle("ECG II      x1");
    ui->widget_b->setTitle("SPO2");
    ui->widget_c->setTitle("RESP       x1");

}

DetectionWidget::~DetectionWidget()
{
    delete ui;
}

void DetectionWidget::setWInfo(QStringList strlist)
{
    infol = strlist;
}

void DetectionWidget::setDevID(QString str)
{
    dev_id = str;
}
//设置数据
void DetectionWidget::setMSG(QByteArray pstr)
{

    QStringList stist = QString(pstr).split(":");
    if(stist.at(1) == dev_id&&stist.size()>=17){
        ui->widget_a->setCurrentTemp(stist.at(3).toInt());
        ui->widget_b->setCurrentTemp(stist.at(4).toInt());
        ui->widget_c->setCurrentTemp(stist.at(5).toInt());

        ui->label_A_1->setText(stist.at(3));
        ui->label_A_2->setText(stist.at(4));
        ui->label_A_3->setText(stist.at(5));
        ui->label_A_4->setText(stist.at(6));

        ui->label_B_1->setText(stist.at(4));
        ui->label_B_2->setText(stist.at(9));
        ui->label_B_3->setText(stist.at(10));

        ui->label_C_2->setText(stist.at(11));
        ui->label_C_3->setText(stist.at(12));
        ui->label_C_4->setText(stist.at(13));

        ui->label_D_1->setText(stist.at(5));
        ui->label_D_2->setText(stist.at(14));
        ui->label_D_3->setText(stist.at(15));
        ui->label_D_4->setText(stist.at(16));
        ui->label_id->setText(stist.at(17));
    }
    infol = stist;
}

void DetectionWidget::on_pushButton_a_clicked()
{
    CreatInfoWidget w;
    w.setWInfo(infol);
    w.exec();
}
