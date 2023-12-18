#include "widget.h"
#include "addservice.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    tableWidget = new QTableWidget(this);
    createTable();
    populateTable();

    QPushButton *addButton = new QPushButton("Добавить услугу", this);
    connect(addButton, &QPushButton::clicked, this, &Widget::addService);

    QPushButton *removeButton = new QPushButton("Удалить услугу", this);
    connect(removeButton, &QPushButton::clicked, this, &Widget::removeService);

    QPushButton *saveButton = new QPushButton("Сохранить", this);
    connect(saveButton, &QPushButton::clicked, this, &Widget::saveData);

    layout->addWidget(tableWidget);
    layout->addWidget(addButton);
    layout->addWidget(removeButton);
    layout->addWidget(saveButton);
}

Widget::~Widget()
{
}

void Widget::createTable()
{
    tableWidget->setColumnCount(4);
    tableWidget->setHorizontalHeaderLabels({"Название услуги", "Наименование специалиста", "Стоимость услуги", "Время оказания услуги"});
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void Widget::populateTable()
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

void Widget::addService()
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

void Widget::removeService()
{
    int currentRow = tableWidget->currentRow();
    if (currentRow >= 0) {
        tableWidget->removeRow(currentRow);
    }
}

void Widget::saveData()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить данные", "", "Текстовые файлы (*.txt)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            int rowCount = tableWidget->rowCount();
            int columnCount = tableWidget->columnCount();
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
