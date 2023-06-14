#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updataCount();

    //网格初始化
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++){
            grids1[i][j]=new QPushButton("0");
            gridLayout1->addWidget(grids1[i][j],i,j,1,1);
        }
    for(int i=0;i<16;i++)
        for(int j=0;j<16;j++){
            grids2[i][j]=new QPushButton("0");
            gridLayout2->addWidget(grids2[i][j],i,j,1,1);
        }

     ui->MineSweeeperWindow1->setLayout(gridLayout1);
     ui->MineSweeeperWindow2->setLayout(gridLayout2);
     ui->MineSweeeperWindow1->hide();
     ui->MineSweeeperWindow2->hide();

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



//开始(暂停)，重置计数器
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


//绘制地图,无炸弹:0,有炸弹:1
void MainWindow::setMap(){

    if(this->level == 1){
    ui->MineSweeeperWindow1->show();
    ui->MineSweeeperWindow2->hide();
    }
    else{

        ui->MineSweeeperWindow2->show();
        ui->MineSweeeperWindow1->hide();
    }


//    //使用数组保存地图信息
//    int map[this->area][this->area];
//    //初始化地图，无炸弹
//    for(int i=0;i<this->area;i++)
//        for(int j=0;j<this->area;j++)
//            map[i][j] = 0;





}


void MainWindow::on_primary_triggered()
{
    this->setLevel(1);
    this->setMap();

}

void MainWindow::on_intermediate_triggered()
{
    this->setLevel(2);
    this->setMap();
}
