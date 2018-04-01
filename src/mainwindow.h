#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMouseEvent>
#include <QString>
#include <QPainter>
#include <QLabel>
#include <QTextItem>
#include <QToolTip>


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void mousePressEvent ( QMouseEvent * event );

private slots:
    void on_actionQuit_triggered();


private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
