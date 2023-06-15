#include "mainwindow.h"

bool MainWindow::checkGridsAround(int map[16][16],int r,int c,int n){

    if(r-1>=0&&c-1>=0)
        if(map[r-1][c-1]==1)
            return false;

    if(r-1>0)
        if(map[r-1][c]==1)
            return false;

    if(r-1>=0&&c+1<n)
        if(map[r-1][c+1]==1)
            return false;

    if(c-1>=0)
        if(map[r][c-1]==1)
            return false;

    if(c+1<n)
        if(map[r][c+1]==1)
            return false;

    if(r+1<n&&c-1>=0)
        if(map[r+1][c-1]==1)
            return false;

    if(r+1<n)
        if(map[r+1][c]==1)
            return false;


    if(r+1<n&&c+1<n)
        if(map[r+1][c+1]==1)
            return false;


    return true;

}