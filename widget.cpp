#include "widget.h" // Класс
#include "addservice.h" // класс добавления виджета
#include <QVBoxLayout> // Заполняет виджеты сверху вниз
#include <QPushButton> // Для создания кнопок
#include <QHeaderView> // Для звголовков
#include <QMessageBox> // Для диалоговых окон
#include <QFile> // Для сохранения
#include <QTextStream> // Для сохранения Без них 3-х все сломается(((9(
#include <QFileDialog> // Для сохранения

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);  // создание вертикального (без него сломается)

    tableWidget = new QTableWidget(this); //таблица новая
    createTable(); //создал
    populateTable(); // ЗАполнил

    QPushButton *addButton = new QPushButton("Добавить услугу", this);
    connect(addButton, &QPushButton::clicked, this, &Widget::addService); // связываю кнопку "добавить" со слотом addservice

    QPushButton *removeButton = new QPushButton("Удалить услугу", this);
    connect(removeButton, &QPushButton::clicked, this, &Widget::removeService); // также связываю

    QPushButton *saveButton = new QPushButton("Сохранить", this);
    connect(saveButton, &QPushButton::clicked, this, &Widget::saveData); // Всё так же

    layout->addWidget(tableWidget); // добавляю виджеты в тот самый вертикальный лайаут
    layout->addWidget(addButton);
    layout->addWidget(removeButton);
    layout->addWidget(saveButton);
}

Widget::~Widget() // Деструктор. Пусть будет
{
}

void Widget::createTable() // создание самой таблицы
{
    tableWidget->setColumnCount(4);
    tableWidget->setHorizontalHeaderLabels({"Название услуги", "Наименование специалиста", "Стоимость услуги", "Время оказания услуги"});
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void Widget::populateTable() // заполнеиние их по умолчанию
{
    tableWidget->setRowCount(2);

    QTableWidgetItem *item1 = new QTableWidgetItem("Услуга 1");
    QTableWidgetItem *item2 = new QTableWidgetItem("Специалист 1");
    QTableWidgetItem *item3 = new QTableWidgetItem("1000");
    QTableWidgetItem *item4 = new QTableWidgetItem("60");

    tableWidget->setItem(0, 0, item1);
    tableWidget->setItem(0, 1, item2);
    tableWidget->setItem(0, 2, item3);
    tableWidget->setItem(0, 3, item4);

    QTableWidgetItem *item5 = new QTableWidgetItem("Услуга 2");
    QTableWidgetItem *item6 = new QTableWidgetItem("Специалист 2");
    QTableWidgetItem *item7 = new QTableWidgetItem("650");
    QTableWidgetItem *item8 = new QTableWidgetItem("20");

    tableWidget->setItem(1, 0, item5);
    tableWidget->setItem(1, 1, item6);
    tableWidget->setItem(1, 2, item7);
    tableWidget->setItem(1, 3, item8);
}

void Widget::addService() //функция добавления новой
{
    AddService addServiceDialog(this);
    if (addServiceDialog.exec() == QDialog::Accepted) {
        QTableWidgetItem *item1 = new QTableWidgetItem(addServiceDialog.getServiceName());
        QTableWidgetItem *item2 = new QTableWidgetItem(addServiceDialog.getSpecialistName());
        QTableWidgetItem *item3 = new QTableWidgetItem(addServiceDialog.getServiceCost());
        QTableWidgetItem *item4 = new QTableWidgetItem(addServiceDialog.getServiceTime());

        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, item1);
        tableWidget->setItem(row, 1, item2);
        tableWidget->setItem(row, 2, item3);
        tableWidget->setItem(row, 3, item4);
    }
}

void Widget::removeService() // функция удаления
{
    int currentRow = tableWidget->currentRow();
    if (currentRow >= 0) {
        tableWidget->removeRow(currentRow);
    }
}

void Widget::saveData() // сохранение
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить данные", "", "Текстовые файлы (*.txt)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            int rowCount = tableWidget->rowCount();
            int columnCount = tableWidget->columnCount();
            // далее прохожусь по всем ячейкам
            for (int row = 0; row < rowCount; ++row) {
                for (int column = 0; column < columnCount; ++column) {
                    QTableWidgetItem *item = tableWidget->item(row, column);
                    if (item) {
                        out << item->text() << ",";
                    }
                }
                out << "\n";
            }
            file.close();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось сохранить данные");
        }
    }
}
