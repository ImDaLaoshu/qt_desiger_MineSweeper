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
            grids1[i][j]=new QPushButton("");
//            QString result=QString::number(i)+","+QString::number(j);
//            grids1[i][j]->setText(result);
            //绑定槽函数
            connect(grids1[i][j], &QPushButton::clicked, this, &MainWindow::sweeperGrids);
            gridLayout1->addWidget(grids1[i][j],i,j,1,1);
        }
    for(int i=0;i<16;i++)
        for(int j=0;j<16;j++){
            grids2[i][j]=new QPushButton("");
//            QString result=QString::number(i)+","+QString::number(j);
//            grids2[i][j]->setText(result);
            //绑定槽函数
            connect(grids2[i][j], &QPushButton::clicked, this, &MainWindow::sweeperGrids);
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

    int numberOfMines,area;
    srand(time(0));
    if(this->level == 1){
    ui->MineSweeeperWindow1->show();
    ui->MineSweeeperWindow2->hide();
    numberOfMines = 10;
    area = 9;
    }
    else{
        ui->MineSweeeperWindow2->show();
        ui->MineSweeeperWindow1->hide();
        numberOfMines = 40;
        area = 16;
    }



    //初始化地图，无炸弹
    for(int i=0;i<area;i++)
        for(int j=0;j<area;j++)
            map[i][j] = 0;


    //随机生成炸弹
    int minNumber = 0;    // 随机数的最小值
    int maxNumber = (area*area)-1;  // 随机数的最大值
    int count = numberOfMines;       // 需要生成的随机数数量

    std::vector<int> numbers;
    for (int i = minNumber; i <= maxNumber; ++i) {
        numbers.push_back(i);
    }

    std::random_device rd;
    std::mt19937 generator(rd());

    std::shuffle(numbers.begin(), numbers.end(), generator);

    for (int i = 0; i < count; ++i) {
        map[numbers[i]/area][numbers[i]%area-1]=1;
//        if(count == 10){
//            int row = numbers[i]/area;
//            int colum = numbers[i]%area-1;

//            grids1[row][colum]->setText("1");
//        }
//        else{
//            int row = numbers[i]/area;
//            int colum = numbers[i]%area-1;

//            grids2[row][colum]->setText("1");
//        }
    }


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


void MainWindow::sweeperGrids(){

    QPushButton *senderButton = qobject_cast<QPushButton*>(sender());
    int row, column, rowSpan, columnSpan;
    //获取网格坐标
    if(this->level == 1)
        gridLayout1->getItemPosition(gridLayout1->indexOf(senderButton),&row, &column, &rowSpan, &columnSpan);
    else
        gridLayout2->getItemPosition(gridLayout2->indexOf(senderButton),&row, &column, &rowSpan, &columnSpan);

//    //分割字符串，获取网格坐标
//    QString str = senderButton->text();
//    std::string stdStr = str.toStdString();

//    std::stringstream ss(stdStr);
//    std::vector<int> numbers;

//    std::string segment;
//    while (std::getline(ss, segment, ',')) {
//        int number;
//        std::istringstream(segment) >> number;
//        numbers.push_back(number);
//    }

//        int r = numbers[0];
//        int c = numbers[1];

        if(this->map[row][column] == 1){
             QIcon icon(":/image/bomb.png");
            senderButton->setIcon(icon);
            QMessageBox::StandardButton sbutton;
            sbutton = QMessageBox::question(this,"西奈","小心手雷  w(ﾟДﾟ)w",
                                           QMessageBox::Yes | QMessageBox::No);
            senderButton->setEnabled(false);

        }



        std::cout<<row<<","<<column<<std::endl;


}


