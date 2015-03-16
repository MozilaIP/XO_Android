#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <stdlib.h>
#include <QMainWindow>
#include <QtGui>
#include <QLabel>
#include <iostream>
#include <QPushButton>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


public:
QPushButton *PGrid[3][3];
QString grid[3][3];
QString Turn;
int turn;
QPixmap X;
QPixmap O;
QPixmap Empty;
QPixmap Img[2][9]; //[theme][image]
bool Win;
bool ChosenTheme;
int ic;
short WinX, WinO;
//QLabel *PGrid[3][3];

public slots:
void Cell00Click();
void Cell01Click();
void Cell02Click();
void Cell10Click();
void Cell11Click();
void Cell12Click();
void Cell20Click();
void Cell21Click();
void Cell22Click();
void NewGame();
void DisplayGrid();
//void CheckResult();
void PaintAllGrey();
void CheckWhoseWon(int y, int x);
void ChangeTheme(int);
//void EnableRow();
//void EnableColumn();
//QString CheckLines();
//QString CheckDiagonal();

};

#endif // MAINWINDOW_H
