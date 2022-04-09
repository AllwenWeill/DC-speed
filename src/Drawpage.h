#ifndef DRAWPAGE_H
#define DRAWPAGE_H
#include <QMainWindow>
#include <QMainWindow>
#include <QApplication>
#include <QtCharts/QChartView>//显示图表
#include <QtCharts/QLineSeries>//线系列
#include <QDoubleSpinBox>
#include <QDebug>
#include <QBarSet>
#include <QBarSeries>
#include <QGridLayout>
#include <QWidget>
#include <QSplineSeries>
#include <QLabel>
#include <QString>
QT_CHARTS_USE_NAMESPACE//QtChart名空间
class Drawpage : public QObject
{
public:
    explicit Drawpage(QObject *parent = nullptr);
    QChart *startDraw();//折线
    QChart *startDraw1();//直方图
    QChart *startDraw2();//曲线
    QLabel *startDraw3();//label
signals:
public slots:
    void showDrawpage();
};

#endif // DRAWPAGE_H
