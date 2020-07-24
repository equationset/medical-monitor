#pragma execution_character_set("utf-8")

#include <QDebug>
#include "creatinfowidget.h"
#include "ui_creatinfowidget.h"
#include <QMessageBox>

CreatInfoWidget::CreatInfoWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreatInfoWidget)
{
    ui->setupUi(this);
    setWindowTitle("创建病人信息");//设置窗体名称
}

CreatInfoWidget::~CreatInfoWidget()
{
    delete ui;
}

void CreatInfoWidget::setWInfo(QStringList plist)
{
    ui->lineEdit_a->setText(plist.at(18));
    ui->lineEdit_b->setText(plist.at(19));
    ui->lineEdit_c->setText(plist.at(20));
    ui->lineEdit_d->setText(plist.at(21));
    ui->lineEdit_d->setText(plist.at(22));
}

void CreatInfoWidget::on_pushButton_a_clicked()
{
    QString stra = ui->lineEdit_a->text();
    QString strb = ui->lineEdit_b->text();
    QString strc = ui->lineEdit_c->text();
    QString strd = ui->lineEdit_d->text();
    QString stre = ui->lineEdit_d->text();


    done(0);
}

void CreatInfoWidget::on_pushButton_b_clicked()
{
    done(0);
}
