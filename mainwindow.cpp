#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include <QMainWindow>
#include <QtGui>
#include <QLabel>
#include <iostream>
#include <QPushButton>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);




    QObject::connect(ui->cell_0_0, SIGNAL(clicked()), this, SLOT(Cell00Click()));
    QObject::connect(ui->cell_0_1, SIGNAL(clicked()), this, SLOT(Cell01Click()));
    QObject::connect(ui->cell_0_2, SIGNAL(clicked()), this, SLOT(Cell02Click()));
    QObject::connect(ui->cell_1_0, SIGNAL(clicked()), this, SLOT(Cell10Click()));
    QObject::connect(ui->cell_1_1, SIGNAL(clicked()), this, SLOT(Cell11Click()));
    QObject::connect(ui->cell_1_2, SIGNAL(clicked()), this, SLOT(Cell12Click()));
    QObject::connect(ui->cell_2_0, SIGNAL(clicked()), this, SLOT(Cell20Click()));
    QObject::connect(ui->cell_2_1, SIGNAL(clicked()), this, SLOT(Cell21Click()));
    QObject::connect(ui->cell_2_2, SIGNAL(clicked()), this, SLOT(Cell22Click()));
    QObject::connect(ui->RestartButton, SIGNAL(clicked()), this, SLOT(NewGame()));
    QObject::connect(ui->ThemePicker, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeTheme(int)));

    WinX=0;
    WinO=0;





//    QPushButton **PGrid = new QPushButton* [3];

//    for (int i = 0; i<3; i++)
//        PGrid [i] = new QPushButton [3];

    //QPushButton *PGrid[3][3];


    PGrid [0][0] = ui->cell_0_0;
    PGrid [0][1] = ui->cell_0_1;
    PGrid [0][2] = ui->cell_0_2;
    PGrid [1][0] = ui->cell_1_0;
    PGrid [1][1] = ui->cell_1_1;
    PGrid [1][2] = ui->cell_1_2;
    PGrid [2][0] = ui->cell_2_0;
    PGrid [2][1] = ui->cell_2_1;
    PGrid [2][2] = ui->cell_2_2;

    // [0] - Classic
    // [1] - Pika
    // ############
    // [0] - Background
    // [1] - Empty Cell
    // [2] - Cell O
    // [3] - Cell X
    // [4] - Header
    // [5] - Headers`s shadow
    // [6] - Logo
    // [7] - Options
    // [8] - Replay

    Img [0][0] = QPixmap("://Classic_Theme/bkg.png");
    Img [0][1] = QPixmap("://Classic_Theme/CellEmpty.png");
    Img [0][2] = QPixmap("://Classic_Theme/CellO.png");
    Img [0][3] = QPixmap("://Classic_Theme/CellX.png");
    Img [0][4] = QPixmap("://Classic_Theme/HeaderBG.png");
    Img [0][5] = QPixmap("://Classic_Theme/HeaderBG_Shadow.png");
    Img [0][6] = QPixmap("://Classic_Theme/logo.png");
    Img [0][7] = QPixmap("://Classic_Theme/optoins.png");
    Img [0][8] = QPixmap("://Classic_Theme/replay.png");


    Img [1][0] = QPixmap("://Pika_Theme/bkg.png");
    Img [1][1] = QPixmap("://Pika_Theme/CellEmpty.png");
    Img [1][2] = QPixmap("://Pika_Theme/CellO.png");
    Img [1][3] = QPixmap("://Pika_Theme/CellX.png");
    Img [1][4] = QPixmap("://Pika_Theme/HeaderBG.png");
    Img [1][5] = QPixmap("://Pika_Theme/HeaderBG_Shadow.png");
    Img [1][6] = QPixmap("://Pika_Theme/logo.png");
    Img [1][7] = QPixmap("://Pika_Theme/options.png");
    Img [1][8] = QPixmap("://Pika_Theme/replay.png");


    ChosenTheme = 0; // Classic by default


    ui->Background->setPixmap(Img[0][0]);


NewGame();


}

//turn 1 - X, turn 0 - O

void MainWindow::NewGame()
{
    //ui->ThemePicker->raise();
    ui->ThemeLabel->setText("");

    ui->Header->setPixmap(Img[ChosenTheme][4]);
    ui->Shadow->setPixmap(Img[ChosenTheme][5]);
    ui->Logo->setPixmap(Img[ChosenTheme][6]);
    ui->RestartButton->setIcon(Img[ChosenTheme][8]);



    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            grid [i][j]="";

    MainWindow::turn+=1;
    Win=0;

    if (MainWindow::turn%2==0)
    Turn = "X";

    else
        Turn = "O";


    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
        {
            PGrid[i][j]->setEnabled(true);
            PGrid[i][j]->setIcon(Img[ChosenTheme][1]);
        }

    DisplayGrid();


}

void MainWindow::PaintAllGrey()
{

    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            PGrid[i][j]->setEnabled(false);



}

void MainWindow::DisplayGrid()
{

    ui->WhoseTurn->setText(Turn+" Turn");

    //CheckDiagonal();

    ui->ScoreO->setText(QString::number(WinO));
    ui->ScoreX->setText(QString::number(WinX));

    if (Win==0)
    {
        //int y,x;
        //rows check

        for (int i=0; i<3; i++)
        {
            if (grid[i][0]==grid[i][1] && grid[i][1]==grid[i][2] && grid[i][0]!="")
            {
                //y=i;
                Win=1;
                PaintAllGrey();
                for (int q=0; q<3; q++)
                    PGrid[i][q]->setEnabled(true);
                CheckWhoseWon(i, 0);

            }
        }

        //cols check

        for (int i=0; i<3; i++)
        {
            if (grid[0][i]==grid[1][i] && grid[1][i]==grid[2][i] && grid[0][i]!="")
            {
                //x=i;
                Win=1;
                PaintAllGrey();
                for (int q=0; q<3; q++)
                    PGrid[q][i]->setEnabled(true);
                CheckWhoseWon(0, i);

            }
        }


       // check diags

        if (grid[0][0] == grid[1][1] && grid[1][1]==grid[2][2] && grid[1][1]!="")
        {
            Win=1;
            PaintAllGrey();
            for (int i=0; i<3; i++)
                PGrid[i][i]->setEnabled(true);
            CheckWhoseWon(2, 2);
        }

        if (grid[0][2] == grid[1][1] && grid[1][1]==grid[2][0]  && grid[1][1]!="")
        {
            Win=1;
            PaintAllGrey();
            for (int i=0; i<3; i++)
                PGrid[i][2-i]->setEnabled(true);
            CheckWhoseWon(2, 2);
        }


    }

}

void MainWindow::CheckWhoseWon(int y, int x)
{
    QString Won = grid[y][x];

    if (Won=="X")
        WinX++;

    if (Won=="O")
        WinO++;

}

void MainWindow::ChangeTheme(int index)
{
    ui->ThemeLabel->setText("Restart match to apply theme");

    ChosenTheme=index;


}

//QString MainWindow::CheckDiagonal()
//{
//    if(grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] )
//        return grid[0][0];

//    if(grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
//        return grid[1][1];

//    return "";
//}


void MainWindow::Cell00Click()
{


    ui->WhoseTurn->setText(Turn);
    if (grid[0][0]=="")
        {
        if (Turn == "X")
        {
            ui->cell_0_0->setIcon(Img[ChosenTheme][3]);
            grid[0][0]="X";
            Turn = "O";
        }

        else
        {
            ui->cell_0_0->setIcon(Img[ChosenTheme][2]);
            grid[0][0]="O";
            Turn = "X";
        }


        }
    DisplayGrid();
}

void MainWindow::Cell01Click()
{
    ui->WhoseTurn->setText(Turn);
    if (grid[0][1]=="")
        {
        if (Turn == "X")
        {
            ui->cell_0_1->setIcon(Img[ChosenTheme][3]);
            grid[0][1]="X";
            Turn = "O";
        }

        else
        {
             ui->cell_0_1->setIcon(Img[ChosenTheme][2]);
             grid[0][1]="O";
             Turn = "X";
        }
    }

    DisplayGrid();
}

void MainWindow::Cell02Click()
{
    ui->WhoseTurn->setText(Turn);
    if (grid[0][2]=="")
        {
    if (Turn == "X")
    {
        ui->cell_0_2->setIcon(Img[ChosenTheme][3]);
        Turn = "O";
        grid[0][2]="X";
    }

    else
    {
         ui->cell_0_2->setIcon(Img[ChosenTheme][2]);
        Turn = "X";
        grid[0][2]="O";
    }
}
    DisplayGrid();
}

void MainWindow::Cell10Click()
{
    ui->WhoseTurn->setText(Turn);
    if (grid[1][0]=="")
        {
    if (Turn == "X")
    {
        ui->cell_1_0->setIcon(Img[ChosenTheme][3]);
        Turn = "O";
        grid[1][0]="X";
    }

    else
    {
         ui->cell_1_0->setIcon(Img[ChosenTheme][2]);
        Turn = "X";
        grid[1][0]="O";
    }
    }

    DisplayGrid();
}

void MainWindow::Cell11Click()
{
    ui->WhoseTurn->setText(Turn);
    if (grid[1][1]=="")
        {
    if (Turn == "X")
    {
        ui->cell_1_1->setIcon(Img[ChosenTheme][3]);
        Turn = "O";
        grid[1][1]="X";
    }

    else
    {
         ui->cell_1_1->setIcon(Img[ChosenTheme][2]);
        Turn = "X";
        grid[1][1]="O";
    }
}
    DisplayGrid();
}

void MainWindow::Cell12Click()
{
    ui->WhoseTurn->setText(Turn);
    if (grid[1][2]=="")
        {
    if (Turn == "X")
    {
        ui->cell_1_2->setIcon(Img[ChosenTheme][3]);
        Turn = "O";
        grid[1][2]="X";
    }

    else
    {
         ui->cell_1_2->setIcon(Img[ChosenTheme][2]);
        Turn = "X";
        grid[1][2]="O";
    }
}
    DisplayGrid();
}

void MainWindow::Cell20Click()
{
    ui->WhoseTurn->setText(Turn);
    if (grid[2][0]=="")
        {
    if (Turn == "X")
    {
        ui->cell_2_0->setIcon(Img[ChosenTheme][3]);
        Turn = "O";
        grid[2][0]="X";
    }

    else
    {
         ui->cell_2_0->setIcon(Img[ChosenTheme][2]);
        Turn = "X";
        grid[2][0]="O";
    }
}
    DisplayGrid();
}

void MainWindow::Cell21Click()
{
    ui->WhoseTurn->setText(Turn);
    if (grid[2][1]=="")
        {
    if (Turn == "X")
    {
        ui->cell_2_1->setIcon(Img[ChosenTheme][3]);
        Turn = "O";
        grid[2][1]="X";
    }

    else
    {
         ui->cell_2_1->setIcon(Img[ChosenTheme][2]);
        Turn = "X";
        grid[2][1]="O";
    }
    }

    DisplayGrid();
}

void MainWindow::Cell22Click()
{
    ui->WhoseTurn->setText(Turn);
    if (grid[2][2]=="")
        {
    if (Turn == "X")
    {
        ui->cell_2_2->setIcon(Img[ChosenTheme][3]);
        Turn = "O";
        grid[2][2]="X";
    }

    else
    {
         ui->cell_2_2->setIcon(Img[ChosenTheme][2]);
        Turn = "X";
        grid[2][2]="O";
    }
    }

    DisplayGrid();
}

//QPixmap CellPixm (int y,int x)
//{

//    if (grid[y][x]==NULL)
//        return


//}

MainWindow::~MainWindow()
{
    delete ui;
}

