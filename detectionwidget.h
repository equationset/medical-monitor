#ifndef DETECTIONWIDGET_H
#define DETECTIONWIDGET_H

#include <QWidget>

namespace Ui {
class DetectionWidget;
}
//显示界面
class DetectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DetectionWidget(QWidget *parent = nullptr);
    ~DetectionWidget();

    void setWInfo(QStringList);
public slots:
    void setDevID(QString);//设置设备连接断开
    void setMSG(QByteArray);//当前信息
private slots:
    void on_pushButton_a_clicked();

private:
    Ui::DetectionWidget *ui;
    QString dev_id;//设备id
    QStringList infol;//病人信息

};

#endif // DETECTIONWIDGET_H
