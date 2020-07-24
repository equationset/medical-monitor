#ifndef CREATINFOWIDGET_H
#define CREATINFOWIDGET_H

#include <QDialog>

namespace Ui {
class CreatInfoWidget;
}

class CreatInfoWidget : public QDialog
{
    Q_OBJECT

public:
    explicit CreatInfoWidget(QWidget *parent = nullptr);
    ~CreatInfoWidget();//构造析构
    void setWInfo(QStringList);
private slots:
    void on_pushButton_a_clicked();//创建

    void on_pushButton_b_clicked();//取消

private:
    Ui::CreatInfoWidget *ui;
};

#endif // CREATINFOWIDGET_H
