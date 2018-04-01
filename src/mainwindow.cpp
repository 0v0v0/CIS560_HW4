#include "mainwindow.h"
#include <ui_mainwindow.h>
int draws;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mygl->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::exit();
}

void MainWindow::mousePressEvent ( QMouseEvent * event )
{
    int x,y;
    x=event->x();
    y=event->y();
    QString pStr;
    pStr ="x="+QString::number(draws)+", y="+QString::number(y)+" draws="+QString::number(draws);
    QToolTip::showText(mapToGlobal(event->pos()) ,pStr);
}
