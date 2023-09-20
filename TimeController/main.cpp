#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    server server_;
    qDebug() << "Started!";
    return a.exec();
}
