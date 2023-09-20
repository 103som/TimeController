#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    QPixmap logo;
    QString path = QDir::currentPath() + "/Images" + "/logo.png";
    path.replace("\\", "/");
    qDebug() << path;

    ui->label_2->setFont(QFont("Arial", 14, QFont::Bold));
    ui->label_2->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    ui->label_2->setText("00:00:00");
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));

    //logo.load(path);
    //ui->logo_label->setPixmap(logo);
    //ui->logo_label->setScaledContents(true);

    //int pixWidth = logo.width();
    //int labelWidth = ui->logo_label->width();

    //int factor = double(labelWidth) / pixWidth;
    //ui->logo_label->setFixedWidth(factor * ui->logo_label->pixmap().width());
    //ui->logo_label->setFixedHeight(factor * ui->logo_label->pixmap().height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_1_clicked()
{
    close();
}


void MainWindow::on_pushButton_3_clicked()
{
    showMinimized();
}


void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::slotTimerAlarm()
{
    /* Ежесекундно обновляем данные по текущему времени
     * Перезапускать таймер не требуется
     * */
    totalTime += 1;

    int hours = totalTime / 3600;
    int minutes = (totalTime - hours * 3600) / 60;
    int seconds = totalTime - hours * 3600 - minutes * 60;

    std::string strHours = std::to_string(hours);
    if (hours <= 9) {
        strHours = "0" + strHours;
    }

    std::string strMinutes = std::to_string(minutes);
    if (minutes <= 9) {
        strMinutes = "0" + strMinutes;
    }

    std::string strSeconds = std::to_string(seconds);
    if (seconds <= 9) {
        strSeconds = "0" + strSeconds;
    }

    const std::string str = (strHours + ":" + strMinutes + ":" + strSeconds);
    const QString qstr = QString::fromStdString(str);
    ui->label_2->setText(qstr);
}

void MainWindow::on_pushButton_2_clicked()
{
    if (checkCondition) {
        totalTime = 0;
        checkCondition = false;
    }

    if (timerActive) {
        timer->stop();
        timerActive = false;
    } else {
        timer->start(1000);
        timerActive = true;
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    timer->stop();
    ui->label_2->setText("00:00:00");
    timerActive = false;
    checkCondition = true;
}


void MainWindow::on_pushButton_4_clicked()
{
    q = new secondWindow();
    q->resize(800, 400);
    q->show();
}

