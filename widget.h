#ifndef WIDGET_H // Чтобы не было многократное включение одного и того же
#define WIDGET_H

#include <QWidget>
#include <QTableWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
// Отличие слота от обычного привата - могут быть вызваны любым компонентом
private slots:
    void addService(); // Это слот для добавления услуги
    void removeService(); // Удаление услуги
    void saveData(); // Для сохранения данных

private:
    QTableWidget *tableWidget; // Для отображения услуг

    void createTable(); // Для создания таблицы
    void populateTable(); // Для заполнения двумя услугами изначально
};

#endif // WIDGET_H
