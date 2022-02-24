#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QString>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char alpha[]="abcdefghiklmnopqrstuvwxyz";

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

vector <char> Matrix()
{
    vector <char> matrix;


    if (matrix.size() <= 25)
    {
        for(char c : alpha)
        {
            if (matrix.size() == 25)
            {
                break;
            }
            auto it = find(matrix.begin(), matrix.end(), c);
            if (it != matrix.end())
            {
                continue;
            }
            matrix.push_back(c);
        }
    }
    return matrix;
}


void MainWindow::Decrypt()
{
    QString len;
    QString msg = ui->plainTextEdit->toPlainText().replace("j", "i", Qt::CaseInsensitive).toLower();

    auto cypherMatrix = Matrix();
    vector<int> pos_s;

    for (int i = 0; i < msg.length();i++)
    {
        char c = msg.at(i).toLatin1();
        int pos = 0;
        for (char ac : alpha) {
            if (ac == c) {
                break;
            }
            pos += 1;
        }
        int x = pos % 5;
        int y = pos / 5;

        pos_s.push_back(x);
        pos_s.push_back(y);
    }

    int mid = pos_s.size() / 2;
    for (int i = 0; i < mid; i++) {
        len += QChar::fromLatin1(cypherMatrix[pos_s[i] + pos_s[i+mid]*5]);
    }

    ui->plainTextEdit_2->setPlainText(len);
}

void MainWindow::Encrypt()
{
    QString len;
    QString msg = ui->plainTextEdit->toPlainText().replace("j", "i", Qt::CaseInsensitive).toLower();

    auto cypherMatrix1 = Matrix();
    vector<int> pos_s;

    for (int i = 0; i < msg.length();i++)
    {
        char c = msg.at(i).toLatin1();
        int pos = 0;
        for (char ac : alpha) {
            if (ac == c) {
                break;
            }
            pos += 1;
        }
        int x = pos % 5;
        int y = pos / 5;

        pos_s.insert(begin(pos_s) + pos_s.size() / 2, x);
        pos_s.push_back(y);
    }

    for (int i = 0; i < pos_s.size(); i += 2) {
        len += QChar::fromLatin1(cypherMatrix1[pos_s[i] + pos_s[i+1]*5]);
    }

    ui->plainTextEdit_2->setPlainText(len);
}

void MainWindow::on_pushButton_clicked()
{

    if (ui->checkBox->isChecked())
    {
        Decrypt();
    }
    else
    {
        Encrypt();
    }

}
