#pragma execution_character_set("utf-8")
#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    setWindowTitle("检测仪");
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_pushButton_a_clicked()
{
    //判断是否可以登录
    if(ui->lineEdit_a->text() == ui->lineEdit_b->text()){
        done(1);
    }
}
//退出
void LoginWidget::on_pushButton_b_clicked()
{
    exit(0);
}
