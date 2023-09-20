#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

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
#include <QtGui>
#include <QtCore>
#include <QTableWidget>
#include <QHeaderView>

QT_BEGIN_NAMESPACE
namespace Ui {
class secondWindow;
}
QT_END_NAMESPACE

class secondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit secondWindow(QWidget *parent = nullptr);
    ~secondWindow();

private:
    QTableWidget *tableWidget;
    Ui::secondWindow *ui;

private:
    /* Метод для настройки интерфейса,
     * в данном методе будет выполняться заполнение QTableWidget
     * записями из таблицы
     * */
    void createUI(const QStringList &headers);
};

#endif // SECONDWINDOW_H
