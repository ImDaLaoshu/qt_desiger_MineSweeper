#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include <QGridLayout>
#include <QTimer>
#include <QSignalMapper>
#include <QString>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include<string>
#include <sstream>
#include <vector>
#include <queue>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



    //退出函数
    void closeEvent(QCloseEvent *event);

    QTimer *timer_up = new QTimer(this);

    //计时器开始函数
    void startCount();
    //计时器暂停函数
    void stopCount();
    //计时器重置函数
    void resetCount();
    //计时器更新函数
    void updataCount();
    //时间计算
    void calculateCount();

    //难度设置,初级难度为1，中级难度为2
    void setLevel(int L){
    this->level=L;
    }

    //绘制地图
    void setMap();

    //判断方格周边八个方格是否无雷
    bool checkGridsAround(int map[16][16],int r,int c,int n);
    //获得方格周边八个方格地雷数量
    int getAroundMine(int map[16][16],int r,int c,int n);

private slots:
    void on_exit_triggered();


    void on_pushButtton_start_clicked();

    void on_pushButton_reset_clicked();

    void on_primary_triggered();

    void on_intermediate_triggered();

    void sweeperGrids();

private:
    Ui::MainWindow *ui;
    //计时器时间
    int count_h =0;
    int count_m =0;
    int count_s =0;

    //计数器工作状态
     bool workingCount = false;

     //难度,默认为初级难度1
     int level = 1;

     //网格创建
     QPushButton *grids1[9][9];
     QPushButton *grids2[16][16];
     QGridLayout *gridLayout1=new QGridLayout;
     QGridLayout *gridLayout2=new QGridLayout;

     //使用数组保存地图信息
     int map[16][16];
};
#endif // MAINWINDOW_H
