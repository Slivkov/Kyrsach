#ifndef WIDGET_H // Чтобы не было многократное включение одного и того же
#define WIDGET_H

#include <QWidget>
#include "ui_widget.h"
#include <QTableWidget>



class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
// Отличие слота от обычного привата - могут быть вызваны любым компонентом в классе.

// слот вызывается в ответ на сигналы. у меня клик мышью в основном
private slots:
    void addService(); // Это слот для добавления услуги
    void removeService(); // Удаление услуги
    void saveData(); // Для сохранения данных
    void loadData(); // НОВОЕ!!! Для загрузки данных из файла
    void copyService(); // НОВОЕ!! Слот для копирования.
    void editService(int row, int column); // НОВОЕ! Для изменения
    void showHelp(); // Для "Руководство"
    void showAbout(); // Для "О программе"
    void exitApplication(); // для выхода





private:
    Ui::Widget *ui;
    QTableWidget *tableWidget; // Для отображения услуг
    QMenu* helpMenu;

    void createTable(); // Для создания таблицы
    void populateTable(); // Для заполнения двумя услугами изначально
    void clearTable(); // НОВОЕ!!! Для очистки таблицы (иначе каша будет)

};

#endif // WIDGET_H
