#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QDir>
#include <QPixmap>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QFont>
#include <iostream>
#include <ctime>
#include <string>
#include "secondwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void slotTimerAlarm();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

private:
    secondWindow* q;
    QTimer *timer;
    time_t totalTime = 0;
    bool checkCondition = true;
    bool timerActive = false;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
