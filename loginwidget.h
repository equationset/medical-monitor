#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QDialog>

namespace Ui {
class LoginWidget;
}
//登录窗口
class LoginWidget : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();//构造析构

private slots:
    void on_pushButton_a_clicked();//登录按钮

    void on_pushButton_b_clicked();//取消按钮

private:
    Ui::LoginWidget *ui;
};

#endif // LOGINWIDGET_H
