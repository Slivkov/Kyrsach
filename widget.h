#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void addService();
    void removeService();
    void saveData();

private:
    QTableWidget *tableWidget;

    void createTable();
    void populateTable();
};

#endif // WIDGET_H
