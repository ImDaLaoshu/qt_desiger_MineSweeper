#include "mainwindow.h"

bool MainWindow::checkGridsAround(int map[16][16],int r,int c,int n){

    for (int i=r-1;i<=r+1;i++)
        for(int j=c-1;j<=c+1;j++)
            if(i>=0&&i<n&&j>=0&&j<n)
                if(map[i][j] == 1)
                    return false;

    return true;

}


int MainWindow::getAroundMine(int map[16][16],int r,int c,int n){


    int number=0;

    for (int i=r-1;i<=r+1;i++)
        for(int j=c-1;j<=c+1;j++)
            if(i>=0&&i<n&&j>=0&&j<n)
                if(map[i][j] == 1)
                    number++;
    return number;
}

void MainWindow::openGridsAround(int (*map)[16], int r, int c, int n){

    if(map[r][c] == 1)
        return;

    map[r][c] = 2;

    for (int i=r-1;i<=r+1;i++)
        for(int j=c-1;j<=c+1;j++)
            if(i>=0&&i<n&&j>=0&&j<n){
                if(this->checkGridsAround(map,i,j,n) && map[i][j]!=2)
                    openGridsAround(map,i,j,n);

                 map[i][j] =2;

            }

}
