#include "mainwindow.h"
#include <QApplication>
#include <QtCharts/QChartView>//显示图表
#include <QtCharts/QLineSeries>//线系列
#include <QDoubleSpinBox>
#include <QPushButton>
QT_CHARTS_USE_NAMESPACE//QtChart名空间
int main(int argc, char *argv[])
{
//测试的50组数据：31,41,38,28,51,39,45,42,33,43,41,51,37,51,26,23,34,38,40,48,33,35,40,41,43,46,58,50,48,47,46,53,43,33,39,45,41,34,33,29,40,44,37,35,40,38,30,53,44,53
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(400, 240);
    w.show();
    return a.exec();
}
