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
#include <QPushButton>
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
    void Logo_label(MainWindow* ptr);
    void strToint();
    void sortDatas(QVector<int> &speedDatas);
    void grouping(QVector<int> &speedDatas, int speedInterval, int groupNum);
    void invaild_randCarSpeed();
    void vaild_randCarSpeed();
    void clearDatas();
    void select_randCarSpeed(int low, int high, int num);
    void Aw_label(MainWindow* ptr,QString str,int move_x,int move_y);
    void showExampleData();
public slots:
    void getSpeedData();
};
//设置Button的函数,分别传入myWidget的this指针，需要按键显示的字符串str,按键的长rsize_x,宽rsize_y;按键的初始位置横坐标move_x和纵坐标move_y
QPushButton* set_btn(MainWindow* ptr, QString str, int rsize_x, int rsize_y, int move_x, int move_y);
#endif // MAINWINDOW_H
