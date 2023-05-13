#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap logo;
    QString path = QDir::currentPath() + "/Images" + "/logo.png";
    path.replace("\\", "/");
    qDebug() << path;

    logo.load(path);
    ui->logo_label->setPixmap(logo);
    ui->logo_label->setScaledContents(true);

    int pixWidth = logo.width();
    int labelWidth = ui->logo_label->width();

    int factor = double(labelWidth) / pixWidth;
    ui->logo_label->setFixedWidth(factor * ui->logo_label->pixmap().width());
    ui->logo_label->setFixedHeight(factor * ui->logo_label->pixmap().height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

