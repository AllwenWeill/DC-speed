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
QString initCarSpeed;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Drawpage *ntr = new Drawpage;
    Aw_label(this,"@Aw_Tech",160,220);
    Logo_label(this);
    edit->setPlaceholderText("请输入50个车速值 ");
    //main_label(this);
    main_edit(this);
    connect(set_btn(this,"确定",80,30,220,170), &QPushButton::clicked, ntr, &Drawpage::showDrawpage);
    connect(set_btn(this,"获取",80,30,100,170), &QPushButton::clicked, this, &MainWindow::getSpeedData);
    connect(set_btn(this,"摇一摇(invaild)",100,30,300,80), &QPushButton::clicked, this, &MainWindow::invaild_randCarSpeed);
    connect(set_btn(this,"摇一摇(vaild)",100,30,300,110), &QPushButton::clicked, this, &MainWindow::vaild_randCarSpeed);
    connect(set_btn(this,"示例数据",100,30,300,140),&QPushButton::clicked, this, &MainWindow::showExampleData);
    setWindowTitle("DC-speed v1.2");
}
void MainWindow::clearDatas(){
    speedDatas.clear();
    speedGroup.clear();
    midDatas.clear();
    qDebug()<<"数据已清除，内存已释放";
}
void MainWindow::showExampleData(){
    edit->clear();
    clearDatas();
    edit->insertPlainText("31,41,38,28,51,39,45,42,33,43,41,51,37,51,26,23,34,38,40,48,33,35,40,41,43,46,58,50,48,47,46,53,43,33,39,45,41,34,33,29,40,44,37,35,40,38,30,53,44,53");
}
void MainWindow::invaild_randCarSpeed(){
    edit->clear();
    clearDatas();
    for(int i = 0; i < 50; i++){//城市普通道路限速60
        int tempSpeed = rand()%60;
        if(tempSpeed < 10){
            i--;
            continue;
        }
        edit->insertPlainText(QString::number(tempSpeed));
        if(i != 49)
            edit->insertPlainText(",");
    }
}
void MainWindow::vaild_randCarSpeed(){
    edit->clear();
    clearDatas();
    int L1_low1 = 1, L1_high = 2, L1_low2 = 4, H_low1 = 9, H_high = 18, H_low2 = 9, L2_low1 = 4, L2_high = 2, L2_low2 = 1;
    select_randCarSpeed(10,15,L1_low1);
    edit->insertPlainText(",");
    select_randCarSpeed(15,20,L1_high);
    edit->insertPlainText(",");
    select_randCarSpeed(20,25,L1_low2);
    edit->insertPlainText(",");
    select_randCarSpeed(25,30,H_low1);
    edit->insertPlainText(",");
    select_randCarSpeed(30,40,H_high);
    edit->insertPlainText(",");
    select_randCarSpeed(40,45,H_low2);
    edit->insertPlainText(",");
    select_randCarSpeed(45,50,L2_low1);
    edit->insertPlainText(",");
    select_randCarSpeed(50,55,L2_high);
    edit->insertPlainText(",");
    select_randCarSpeed(55,60,L2_low2);
}
void MainWindow::select_randCarSpeed(int low, int high, int num){
    for(int i = 0; i < num; i++){
        int tempSpeed = rand()%high;
        if(tempSpeed <= low){
            i--;
            continue;
        }
        edit->insertPlainText(QString::number(tempSpeed));
        if(i != num-1)
            edit->insertPlainText(",");
    }
}
void MainWindow::getSpeedData(){
    clearDatas();
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
    edit->move(100,80);
    edit->resize(200,90);
    edit->setParent(ptr);
    edit->show();
}
void MainWindow::strToint(){//输入的文本每两位产生一个标点符号；该函数可完成本文数据拆解并打包到vector功能
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
QPushButton* set_btn(MainWindow* ptr, QString str, int rsize_x, int rsize_y, int move_x, int move_y)
{
    QPushButton *btn = new QPushButton;
    btn->setParent(ptr);                    //将btn对象成为myWidget的子类，从而依附于myWidget窗口
    btn->setText(str);
    btn->resize(rsize_x,rsize_y);                 //设置按键1的固定大小
    btn->move(move_x,move_y);
    btn->show();                          //show以顶层方式弹出窗口控件
    return btn;
}
void MainWindow::Aw_label(MainWindow *ptr, QString str, int move_x, int move_y){
    QFont ft = QFont("Microsoft JhengHei",8,2);               //设置字体
    QPalette pa;            //设置画盘
    pa.setColor(QPalette::WindowText,Qt::gray);
    QLabel *lab = new QLabel;
    //ft.setItalic(true);
    lab->setParent(ptr);
    lab->setText(str);
    lab->setFont(ft);
    lab->setPalette(pa);
    lab->resize(100,15);
    lab->move(move_x,move_y);
    lab->show();
}
void MainWindow::Logo_label(MainWindow *ptr){
    QFont ft = QFont("SimSun",35,2);               //设置字体
    QPalette pa;            //设置画盘
    pa.setColor(QPalette::WindowText,Qt::black);
    QLabel *lab = new QLabel;
    ft.setItalic(true);//设置斜体
    lab->setParent(ptr);
    lab->setText("DC-speed");
    lab->setFont(ft);
    lab->setPalette(pa);
    lab->resize(230,80);
    lab->move(96,0);
    lab->show();
}
MainWindow::~MainWindow()
{

}
