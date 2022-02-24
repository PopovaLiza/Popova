#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QString>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;
char alpha[]="abcdefghijklmnopqrstuvwxyz";

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

const char POLYBIUS[ 5 ][ 5 ] = {
    { 'A', 'B', 'C' , 'D', 'E'},
    { 'F', 'G', 'H' , 'I', 'K'},
    { 'L', 'M', 'N' , 'O', 'P'},
    { 'Q', 'R', 'S' , 'T', 'U'},
    { 'V', 'W', 'X' , 'Y', 'Z'}
};


void MainWindow::Decrypt()
{
    QString c = ui->lineEdit->text();
    int size = -1;
        while ( c[ ++size ] != '\0' ){};

        int *x = new int[ size ];
        int *y = new int[ size ];

        for ( int k = 0; k < size; ++k ){

            for ( int i = 0; i < 5; ++i )
            for ( int j = 0; j < 5; ++j )
                if ( POLYBIUS[ i ][ j ] == c[ k ] ){
                    x[ k ] = j;
                    y[ k ] = i;
                }
        }

        int *z = new int[ 2*size ];

        for ( int k = 0; k < size; ++k )
            z[ k ] = x[ k ];
        for ( int k = size; k < 2*size; ++k )
            z[ k ] = y[ k - size ];

        for ( int k = 0; k < size; ++k ){
            x[ k ] = z[ k*2 ];
            y[ k ] = z[ k*2 + 1 ];
        }

        for ( int k = 0; k < size; ++k )
            c[ k ] = POLYBIUS[ y[ k ] ][ x[ k ] ];

        delete [] z;
        delete [] y;
        delete [] x;
    }

void MainWindow::on_pushButton_clicked()
{

    if (ui->checkBox->isChecked() == true)
    {

    }
    else
    {

    }
}
