#include "secondwindow.h"
#include "./ui_secondwindow.h"
#include <QHeaderView>

secondWindow::secondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::secondWindow)
{
    ui->setupUi(this);

   tableWidget = new QTableWidget(this);
   tableWidget->setColumnCount(5);
   tableWidget->setRowCount(10);
   tableWidget->resize(800, 400);
   tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
   this->createUI(QStringList() << ("Название приложения")
                                << ("Описание")
                                << ("Начало работы")
                                << ("Конец работы")
                                << ("Общее время работы"));
}

secondWindow::~secondWindow()
{
    delete ui;
}

/* Метод для настройки интерфейса,
 * в данном методе будет выполняться заполнение QTableWidget
 * записями из таблицы
 * */
void secondWindow::createUI(const QStringList &headers)
{
    tableWidget->setColumnCount(5); // Указываем число колонок
    tableWidget->setShowGrid(true); // Включаем сетку
    // Разрешаем выделение только одного элемента
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем заголовки колонок
    tableWidget->setHorizontalHeaderLabels(headers);
    // Растягиваем последнюю колонку на всё доступное пространство
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    // Скрываем колонку под номером 0
    tableWidget->hideColumn(0);

    // ВСТАВКА ДАННЫХ.
    //

    // Ресайзим колонки по содержимому



    tableWidget->resizeColumnsToContents();
}
