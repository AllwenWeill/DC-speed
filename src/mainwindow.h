#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QDebug>
#include <QVector>
#include <QTextEdit>
#include <QString>
#include <QApplication>
#include <QtCharts/QChartView>//显示图表
#include <QtCharts/QLineSeries>//线系列
#include <QDoubleSpinBox>
#include "Drawpage.h"
QT_CHARTS_USE_NAMESPACE//QtChart名空间
class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTextEdit* edit = new QTextEdit;//妙！这样类中所有函数皆可使用该对象！
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void main_label(MainWindow* ptr);
    void main_edit(MainWindow* ptr);
    void strToint();
    void sortDatas(QVector<int> &speedDatas);
    void grouping(QVector<int> &speedDatas, int speedInterval, int groupNum);
public slots:
    void getSpeedData();
};

#endif // MAINWINDOW_H
