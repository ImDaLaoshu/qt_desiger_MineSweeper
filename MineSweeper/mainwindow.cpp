#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QFont ft;
//    ft.setPointSize(18);
//    ft.setBold(true);
//    ui->label_h->setFont(ft);
//    ui->label_m->setFont(ft);
//    ui->label_s->setFont(ft);
//    ui->label_h->setAlignment(Qt::AlignCenter);
//    ui->label_m->setAlignment(Qt::AlignCenter);
//    ui->label_s->setAlignment(Qt::AlignCenter);
    updataCount();
}

MainWindow::~MainWindow()
{
    delete ui;
}


//退出功能
void MainWindow::on_exit_triggered()
{
    this->close();
}

void MainWindow::closeEvent(QCloseEvent *event){

    QMessageBox::StandardButton button;
    button = QMessageBox::question(this,"李和鑫你回来","真的要走吗  w(ﾟДﾟ)w",
                                   QMessageBox::Yes | QMessageBox::No);
    if(button == QMessageBox::Yes)
        event->accept();    //确认退出
    else
        event->ignore();    //拒绝退出
}

//计时器

void MainWindow::updataCount(){

    connect(timer_up, &QTimer::timeout, [=](){
        count_s++;
        calculateCount();
    });
}

void MainWindow::calculateCount(){

    if(count_s<10)
        {
            ui->label_s->setText("0" + QString::number(count_s));
        }
        else if(count_s>=10 && count_s<60)
        {
            ui->label_s->setText(QString::number(count_s));
        }
        else
        {
            count_s=0;
            ui->label_s->setText("00");
            count_m++;
            if(count_m<10)
            {
                ui->label_m->setText("0" + QString::number(count_m));
            }
            else if(count_m>=10 && count_m<60)
            {
                ui->label_m->setText(QString::number(count_m));
            }
            else
            {
                count_m=0;
                ui->label_m->setText("00");
                count_h++;
                if(count_h<10)
                {
                    ui->label_h->setText("0" + QString::number(count_h));
                }
                else
                {
                    ui->label_h->setText(QString::number(count_h));
                }
            }
        }
}


void MainWindow::startCount(){

    if(workingCount == false){
        timer_up->start(1000);
        workingCount = true;
    }
}

void MainWindow::stopCount(){

    if(workingCount ==true){
        timer_up->stop();
        workingCount = false;
    }
}

void MainWindow::resetCount(){

    timer_up->stop();
    workingCount = false;
    ui->label_s->setText("00");
    ui->label_m->setText("00");
    ui->label_h->setText("00");
    count_s=0;
    count_m=0;
    count_h=0;

}











void MainWindow::on_pushButtton_start_clicked()
{
    if(workingCount ==false){
        startCount();
        workingCount = true;
        ui->pushButtton_start->setText("暂停");
    }
    else{
        stopCount();
        workingCount = false;
         ui->pushButtton_start->setText("开始");

    }
}

void MainWindow::on_pushButton_reset_clicked()
{
    resetCount();
    ui->pushButtton_start->setText("开始");
}
