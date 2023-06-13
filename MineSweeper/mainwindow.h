#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include <QTimer>

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
    //计时器时间
    int count_h =0;
    int count_m =0;
    int count_s =0;
    //计数器工作状态
     bool workingCount = false;
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



private slots:
    void on_exit_triggered();



    void on_pushButtton_start_clicked();

    void on_pushButton_reset_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
