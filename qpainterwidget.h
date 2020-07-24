#ifndef QPAINTERWIDGET_H
#define QPAINTERWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
class QTimer;
//绘图控件，波形控件
class QPainterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QPainterWidget(QWidget *parent = 0);
    ~QPainterWidget();


    int getCurrentValue();
    void setModel(int);
    void setTitle(QString);
protected:
    void paintEvent(QPaintEvent *);

signals:
    void sendCurrentValue(QString);

public slots:
    void startTimeSlot();
    void stopTimeSlot();
    void accepttimeout();
    void setCurrentTemp(int value);

private:
    QTimer *timer;
    QVector<int>  temperature;
    QVector<int>  simulation_A;//模拟数据
    QVector<int>  simulation_B;//模拟数据
    QVector<int>  simulation_C;//模拟数据
    QList<QPointF> knots;        // 曲线上的点
    QPainterPath smoothCurve;    // 平滑曲线

    int maxStep; //最大数
    int maxValue; //最大值
    int minValue;//最小值
    int recordnum;//记录数
    int model;//模式
    int currentValue;
    QString title;//标题
};

#endif // QPAINTERWIDGET_H
