#include "mainwindow.h"
#include <QApplication>
#include <QtCharts/QChartView>//显示图表
#include <QtCharts/QLineSeries>//线系列
#include <QDoubleSpinBox>
#include <QPushButton>
QT_CHARTS_USE_NAMESPACE//QtChart名空间
using namespace std;
QString str;
QVector<int> speedDatas;
QVector<QVector<int>> speedGroup;
QVector<int> midDatas;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Drawpage *ntr = new Drawpage;
    main_label(this);
    main_edit(this);
    QPushButton* ackButton = new QPushButton;
    QPushButton* getButton = new QPushButton;
    ackButton->setParent(this);
    getButton->setParent(this);
    ackButton->setText("确定");
    getButton->setText("获取");
    ackButton->resize(80,40);
    getButton->resize(80,40);
    ackButton->move(220,160);
    getButton->move(100,160);
    connect(ackButton, &QPushButton::clicked, ntr, &Drawpage::showDrawpage);
    connect(getButton, &QPushButton::clicked, this, &MainWindow::getSpeedData);
    ackButton->show();
    getButton->show();
}
void MainWindow::getSpeedData(){
    str=edit->toPlainText();
    qDebug()<<"str"<<str;
    MainWindow::strToint();
    qDebug()<<"speedData"<<speedDatas;
}
void MainWindow::main_label(MainWindow *ptr){
    QFont ft;               //设置字体
    QPalette pa;            //设置画盘
    ft.setPointSize(16);
    pa.setColor(QPalette::WindowText,Qt::black);
    QLabel *lab = new QLabel;
    lab->setParent(ptr);
    lab->setText("输入车速序列：");
    lab->setFont(ft);
    lab->setPalette(pa);
    lab->resize(200,20);
    lab->move(0,20);
    lab->show();
}
void MainWindow::main_edit(MainWindow *ptr){
    edit->move(100,60);
    edit->resize(200,80);
    edit->setParent(ptr);
    edit->show();
}
void MainWindow::strToint(){//输入的文本每两位产生一个标点符号；该函数可完成本文数据打包到vector功能
    for(int i=0;i<str.size();i+=3){
        QString tempstr;
        for(int j=i;j<i+2;j++){
            tempstr+=str[j];
        }
        speedDatas.push_back(tempstr.toInt());
    }
    MainWindow::sortDatas(speedDatas);
    int speedInterval=(int)(speedDatas[speedDatas.size()-1]-speedDatas[0])/(10-1);
    MainWindow::grouping(speedDatas, speedInterval, 10);
}
void MainWindow::sortDatas(QVector<int> &speedDatas){
    for(int i=0;i<speedDatas.size()-1;i++){
        for(int j=i;j<speedDatas.size();j++){
            if(speedDatas[i]>speedDatas[j]){
                int temp=speedDatas[i];
                speedDatas[i]=speedDatas[j];
                speedDatas[j]=temp;
            }
        }
    }
}
void MainWindow::grouping(QVector<int> &speedDatas, int speedInterval, int groupNum){
    int tempMin=speedDatas[0]+speedInterval+1;
    int lastMin=speedDatas[0]-1;
    for(int i=0;i<groupNum;i++){
        QVector<int> temp;
        int midNum;
        for(int j=0;j<speedDatas.size();j++){
        if(speedDatas[j]<=tempMin&&speedDatas[j]>lastMin){
            temp.push_back(speedDatas[j]);
            }
        }
        speedGroup.push_back(temp);
        if(speedGroup[i].size()%2==1){//odd
            midNum=speedGroup[i][(int)(speedGroup[i].size()/2)];
        }
        else{
            midNum=(int)(speedGroup[i][speedGroup[i].size()/2-1]+speedGroup[i][speedGroup[i].size()/2])/2;
        }
        midDatas.push_back(midNum);
        lastMin=tempMin;
        tempMin+=speedInterval;
    }
}
MainWindow::~MainWindow()
{

}
