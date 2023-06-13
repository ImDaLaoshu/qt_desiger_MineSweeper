#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
