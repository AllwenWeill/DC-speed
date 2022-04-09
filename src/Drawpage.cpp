#include "Drawpage.h"
extern QVector<int> speedDatas;
extern QVector<QVector<int>> speedGroup;
extern QVector<int> midDatas;
Drawpage::Drawpage(QObject *parent): QObject(parent)
{

}
void Drawpage::showDrawpage(){
    QWidget *ptr = new QWidget;//要使用布局管理器必须在widget上使用，因此需要在mainwindow上再添加一个widget
    QMainWindow* wtr = new QMainWindow;
    ptr->setParent(wtr);
    ptr->resize(940,700);
    ptr->setFixedSize(940,700);
    wtr->setCentralWidget(ptr);//将widget设置成mainwindows的中心部件
    QChartView *chartView = new QChartView(startDraw());
    QChartView *chartView1 = new QChartView(startDraw1());
    QChartView *chartView2 = new QChartView(startDraw2());
    QLabel *lab = new QLabel();
    //lab->resize(100,20);
    lab->setText(QString("【85%位车速："+QString::number(48)+"】  |  【15%位车速："+QString::number(33)+"】"));
    //lab->setParent(ptr);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView1->setRenderHint(QPainter::Antialiasing);
    chartView2->setRenderHint(QPainter::Antialiasing);
    //------------label字体设置-------------------------
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::black);
    lab->setPalette(pa);
    QFont ft( "Microsoft YaHei", 20, 75);//第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    //ft.setPointSize(26);//字体大小
    lab->setFont(ft);
    lab->setStyleSheet("background-color:pink");
    //--------------------------------------------------
//    wtr->setCentralWidget(chartView);
//    wtr->setCentralWidget(chartView1);
    wtr->setWindowTitle("AutoDrawCarSpeed");
    wtr->setFixedSize(960, 720);
    QGridLayout *baseLayout = new QGridLayout(ptr);//布局管理器
    baseLayout->addWidget(chartView,0,0);//0,1为排版布局
    baseLayout->addWidget(chartView1,0,1);
    baseLayout->addWidget(chartView2,1,1);
    baseLayout->addWidget(lab,1,0,Qt::AlignLeft);//aligncenter中间对齐
    baseLayout->setMargin(0);//表示控件与窗体的左右边距
    baseLayout->setSpacing(0);//表示各个控件之间的上下间距
    //baseLayout->setColumnStretch()
    wtr->setLayout(baseLayout);
    qDebug()<<"extern speedData"<<speedDatas;
    qDebug()<<"speedGroup"<<speedGroup;
    qDebug()<<"midDatas"<<midDatas;
    wtr->show();
}

QChart* Drawpage::startDraw(){//折线图
        QList<QLineSeries *> m_series;
        QLineSeries *series1 = new QLineSeries();//实例化一个QLineSeries对象
        QLineSeries *series2 = new QLineSeries();//实例化一个QLineSeries对象
        m_series.append(series1);
        m_series.append(series2);
        //设置线条名称
        series1->setName("中位车速区间折线图");
        series2->setName(QString("line " + QString::number(2)));
        //series->setName(QString("line " + QString::number(m_series.count())));
        //设置线条颜色，如果不设置会给默认颜色
        series1->setColor(QColor(255,0,255));
        series2->setColor(QColor(0,255,255));
        //series1->setBrush(QColor(255,0,255));
        //series1->setPen(QColor(255,0,255));
        //设置是否线条可视
        series1->setVisible(true);
        series2->setVisible(false);
        //点标签是否可视
        series1->setPointLabelsVisible(true);
        series2->setPointLabelsVisible(true);
        //点标签颜色
        series1->setPointLabelsColor(QColor(255,255,255));
        series2->setPointLabelsColor(QColor(255,255,255));
        //点标签字体
        series1->setPointLabelsFont(QFont("微软雅黑"));
        series2->setPointLabelsFont(QFont("微软雅黑"));
        //设置点标签显示格式
        series1->setPointLabelsFormat("(@xPoint,@yPoint)");
        series2->setPointLabelsFormat("(@xPoint,@yPoint)");
        //是否切割边缘点标签，默认为true
        series1->setPointLabelsClipping(false);
        series2->setPointLabelsClipping(true);
        //设置点标签是否可视
        series1->setPointsVisible(true);
        series2->setPointsVisible(true);
        //添加坐标点
        for(int i=0;i<midDatas.size();i++){
            series1->append(midDatas[i],speedGroup[i].size());
        }
        series2->append(0, 8);
        series2->append(2, 5);
        series2->append(3, 3);
        series2->append(7, 9);
        series2->append(10, 2);
        *series2 << QPointF(11, 3) << QPointF(13, 8) << QPointF(17, 2) << QPointF(18, 5) << QPointF(20, 7);
        QChart *chart = new QChart();
        chart->setTheme(QChart::ChartThemeBlueCerulean);//设置系统主题
        chart->setAnimationOptions(QChart::AllAnimations);//设置启用或禁用动画
        chart->setLocalizeNumbers(true);//数字是否本地化
        chart->legend()->show();//legend是否显示，show和hide
        chart->addSeries(series1);//添加系列到QChart上
        chart->addSeries(series2);//添加系列到QChart上
        chart->createDefaultAxes();//创建默认轴
        //chart->setTitle("车速累积频率分布曲线");//设置标题
        chart->setTitleBrush(QBrush(QColor(255,170,255)));//设置标题Brush
        chart->setTitleFont(QFont("微软雅黑"));//设置标题字体
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);//底部对齐
        chart->legend()->setBackgroundVisible(true);//设置背景是否可视
        chart->legend()->setColor(QColor(255,128,128,128));//设置颜色
        chart->legend()->setLabelColor(QColor(255,128,255));//设置标签颜色
        chart->legend()->setVisible(true);//设置是否可视
        chart->legend()->setBorderColor(QColor(255,255,170,185));//设置边框颜色
        QFont font = chart->legend()->font();
        font.setItalic(!font.italic());
        chart->legend()->setFont(font);//设置字体为斜体
        font.setPointSizeF(12);
        chart->axisX()->setRange(0,60);
        chart->axisX()->setTitleText("车速(m/s)");
        chart->axisY()->setRange(0,15);
        chart->axisY()->setTitleText("频率");
        chart->legend()->setFont(font);//设置字体大小
        chart->legend()->setFont(QFont("微软雅黑"));//设置字体类型
        return chart;
}
QChart* Drawpage::startDraw1(){//直方图
        //------------------------------------------------------------------------------------------------
        QBarSet* set0 = new QBarSet("十组区间车速直方图");
        QBarSeries *set_series = new QBarSeries();
        for(int i=0;i<midDatas.size();i++){
            *set0<<speedGroup[i].size();
        }
        set_series->append(set0);
        set_series->setVisible(true);
        set_series->setLabelsVisible(true);
        //------------------------------------------------------------------------------------------------
        QChart *chart = new QChart();
        chart->setTheme(QChart::ChartThemeBlueCerulean);//设置系统主题
        chart->setAnimationOptions(QChart::AllAnimations);//设置启用或禁用动画
        chart->setLocalizeNumbers(true);//数字是否本地化
        chart->legend()->show();//legend是否显示，show和hide
        chart->addSeries(set_series);
        chart->createDefaultAxes();//创建默认轴
        //chart->setTitle("车速累积频率分布曲线");//设置标题
        chart->setTitleBrush(QBrush(QColor(255,170,255)));//设置标题Brush
        chart->setTitleFont(QFont("微软雅黑"));//设置标题字体
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);//底部对齐
        chart->legend()->setBackgroundVisible(true);//设置背景是否可视
        chart->legend()->setColor(QColor(255,128,128,128));//设置颜色
        chart->legend()->setLabelColor(QColor(255,128,255));//设置标签颜色
        chart->legend()->setVisible(true);//设置是否可视
        chart->legend()->setBorderColor(QColor(255,255,170,185));//设置边框颜色
        QFont font = chart->legend()->font();
        font.setItalic(!font.italic());
        chart->legend()->setFont(font);//设置字体为斜体
        font.setPointSizeF(12);
        chart->axisX()->setRange(0,60);
        chart->axisX()->setTitleText("车速(m/s)");
        chart->axisY()->setRange(0,15);
        chart->axisY()->setTitleText("频率");
        chart->legend()->setFont(font);//设置字体大小
        chart->legend()->setFont(QFont("微软雅黑"));//设置字体类型
        return chart;
}
QChart* Drawpage::startDraw2(){//曲线图
        QSplineSeries *splineseries = new QSplineSeries;
        splineseries->setName("车速累积频率分布曲线");
        //设置线条颜色，如果不设置会给默认颜色
        splineseries->setColor(QColor(0,255,255));
        //设置是否线条可视
        splineseries->setVisible(true);
        //点标签是否可视
        splineseries->setPointLabelsVisible(false);
        //点标签颜色
        splineseries->setPointLabelsColor(QColor(255,255,255));
        //点标签字体
        splineseries->setPointLabelsFont(QFont("微软雅黑"));
        //设置点标签显示格式
        splineseries->setPointLabelsFormat("(@xPoint,@yPoint)");
        //是否切割边缘点标签，默认为true
        splineseries->setPointLabelsClipping(false);
        //设置点标签是否可视
        splineseries->setPointsVisible(true);
        //添加坐标点
        int sumFrequency = 0;
        for(int i=0;i<midDatas.size();i++){
            sumFrequency += (int)(speedGroup[i].size()*100/50);
            splineseries->append(midDatas[i],sumFrequency);
            qDebug()<<sumFrequency;
        }
        QChart *chart = new QChart();
        chart->setTheme(QChart::ChartThemeBlueCerulean);//设置系统主题
        chart->setAnimationOptions(QChart::AllAnimations);//设置启用或禁用动画
        chart->setLocalizeNumbers(true);//数字是否本地化
        chart->legend()->show();//legend是否显示，show和hide
        chart->addSeries(splineseries);//添加系列到QChart上
        chart->createDefaultAxes();//创建默认轴
       // chart->setTitle("车速累积频率分布曲线");//设置标题
        chart->setTitleBrush(QBrush(QColor(255,170,255)));//设置标题Brush
        chart->setTitleFont(QFont("微软雅黑"));//设置标题字体
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);//底部对齐
        chart->legend()->setBackgroundVisible(true);//设置背景是否可视
        chart->legend()->setColor(QColor(255,128,128,128));//设置颜色
        chart->legend()->setLabelColor(QColor(255,128,255));//设置标签颜色
        chart->legend()->setVisible(true);//设置是否可视
        chart->legend()->setBorderColor(QColor(255,255,170,185));//设置边框颜色
        QFont font = chart->legend()->font();
        font.setItalic(!font.italic());
        chart->legend()->setFont(font);//设置字体为斜体
        font.setPointSizeF(12);
        chart->axisX()->setRange(0,60);
        chart->axisX()->setTitleText("车速(m/s)");
        chart->axisY()->setRange(0,100);
        chart->axisY()->setTitleText("频率");
        chart->legend()->setFont(font);//设置字体大小
        chart->legend()->setFont(QFont("微软雅黑"));//设置字体类型
        return chart;
}
//QLabel* Drawpage::startDraw3(){//label
//    QLabel *lab = new QLabel;

//    return lab;
//}
