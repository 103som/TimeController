#include "mainwindow.h"
#include "secondwindow.h"

#include <QApplication>
#include <QPalette>
#include "app.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setFixedSize(400, 140);
    w.setStyleSheet("background-color: white;");
    w.setWindowFlag(Qt::WindowTitleHint, false);
    w.setWindowFlag(Qt::WindowSystemMenuHint, false);
    w.setWindowTitle("");
    w.show();

    qDebug() << "APP";
    App* app = new App();
    return a.exec();
}
