#include "ui_widget.h"
#include "widget.h" // Класс
#include "addservice.h" // класс добавления виджета
#include <QVBoxLayout> // Заполняет виджеты сверху вниз
#include <QPushButton> // Для создания кнопок
#include <QHeaderView> // Для звголовков
#include <QMessageBox> // Для диалоговых окон
#include <QFile> // Для сохранения файла
#include <QTextStream> // Для сохранения файла Без них 3-х все сломается(((9(
#include <QFileDialog> // Для сохранения файла
#include <QDesktopServices> // НОВОЕ
#include <QMenuBar>


Widget::Widget(QWidget *parent) : QWidget(parent) //конструктор виджет
{
    ui->setupUi(this);

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

    QPushButton *loadButton = new QPushButton("Загрузить", this);  // НОВОЕ! Кнопка для загрузки файлика
    connect(loadButton, &QPushButton::clicked, this, &Widget::loadData);

    QPushButton *copyButton = new QPushButton("Копировать", this);
    connect(copyButton, &QPushButton::clicked, this, &Widget::copyService);

    QPushButton *exitButton = new QPushButton("Выход", this);
    connect(exitButton, &QPushButton::clicked, this, &Widget::exitApplication);



    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *helpMenu = menuBar->addMenu("");
    helpMenu->setIcon(QIcon(":/kek.png"));





    QAction *showHelpAction = new QAction(QIcon(":/rykovod.png"), "Руководство", this);
    connect(showHelpAction, &QAction::triggered, this, &Widget::showHelp);

    QAction *aboutAction = new QAction(QIcon(":/menu.jpg"), "О программе", this);
    connect(aboutAction, &QAction::triggered, this, &Widget::showAbout);


    helpMenu->addAction(showHelpAction);
    helpMenu->addAction(aboutAction);




    connect(tableWidget, &QTableWidget::cellDoubleClicked, this, &Widget::editService); // ДЛЯ ТОГО, ЧТОБЫ ПРИ ДВОЙНОМ КЛИКЕ РЕДАЧИТЬ УСЛУГУ


    layout->setMenuBar(menuBar);
    layout->addWidget(tableWidget); // добавляю виджеты в тот самый вертикальный лайаут
    layout->addWidget(addButton);
    layout->addWidget(removeButton);
    layout->addWidget(saveButton);
    layout->addWidget(loadButton); //Новое для загрузки
    layout->addWidget(copyButton);
    layout->addWidget(exitButton);
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
// НОВОЕ!!!!
void Widget::loadData() // Метод для считывания файла
{
    QString fileName = QFileDialog::getOpenFileName(this, "Загрузить данные", "", "Текстовые файлы (*.txt)");
    if (!fileName.isEmpty()) {
        clearTable(); // Очистим таблицу перед загрузкой новых данных, если не пусто.

        QFile file(fileName); // Открываем выбранный файл для чтения.
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {

            QTextStream in(&file);

            while (!in.atEnd()) { // Здесь код читает выбранный файл
                QString line = in.readLine();
                QStringList fields = line.split(',');
                int row = tableWidget->rowCount();
                tableWidget->insertRow(row);
                for (int column = 0; column < fields.size(); ++column) {
                    QTableWidgetItem *item = new QTableWidgetItem(fields[column]);
                    tableWidget->setItem(row, column, item);
                }
            }
            file.close();
        } else { // Если вдруг беда, то ошибка будет
            QMessageBox::warning(this, "Ошибка", "Не удалось загрузить данные");
        }
    }
}

void Widget::clearTable() // НОВОЕ!!
{
    tableWidget->clearContents(); // Очищаю таблицу!
    tableWidget->setRowCount(0);
}



void Widget::copyService()
{
    int currentRow = tableWidget->currentRow();
    if (currentRow >= 0) {
        int rowCount = tableWidget->rowCount();
        tableWidget->insertRow(rowCount);

        for (int column = 0; column < tableWidget->columnCount(); ++column) {
            QTableWidgetItem *item = new QTableWidgetItem(tableWidget->item(currentRow, column)->text());
            tableWidget->setItem(rowCount, column, item);
        }
    }
}


// НОВОЕ! Метод для редактирования параметров услуги
void Widget::editService(int row, int column)
{
    if (column >= 0 && column < tableWidget->columnCount()) {
        // Создаю окно редактирования услуги.
        AddService editServiceDialog(this);
        editServiceDialog.setWindowTitle("Изменить услугу");

        // Заполняю окно текущими значениями
        editServiceDialog.setServiceName(tableWidget->item(row, 0)->text());
        editServiceDialog.setSpecialistName(tableWidget->item(row, 1)->text());
        editServiceDialog.setServiceCost(tableWidget->item(row, 2)->text());
        editServiceDialog.setServiceTime(tableWidget->item(row, 3)->text());

        // Открываю окно редактирования
        if (editServiceDialog.exec() == QDialog::Accepted) {
            // Обновляем значения
            tableWidget->item(row, 0)->setText(editServiceDialog.getServiceName());
            tableWidget->item(row, 1)->setText(editServiceDialog.getSpecialistName());
            tableWidget->item(row, 2)->setText(editServiceDialog.getServiceCost());
            tableWidget->item(row, 3)->setText(editServiceDialog.getServiceTime());
        }
    }
}

void Widget::showHelp() {
    QString filePath = QCoreApplication::applicationDirPath() + "/rykovod.txt";
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}
void Widget::showAbout() {
     QString filePath = QCoreApplication::applicationDirPath() + "/oprog.txt"; // Не относительный путь к файлу
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}

void Widget::exitApplication() {
    QApplication::quit();
}
