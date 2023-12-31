#ifndef ADDSERVICE_H // проверка наличия
#define ADDSERVICE_H // без него сломается

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class AddService : public QDialog
{
    Q_OBJECT // без него не работает. Для работы со слотами

public:
    AddService(QWidget *parent = nullptr);

    QString getServiceName() const; // Функц. для получения названия услуги
    QString getSpecialistName() const; // ДЛя имени спеца
    QString getServiceCost() const; // Для стоимости
    QString getServiceTime() const; // Для времени


    // НОВОЕ!! Методы для передачи значений в поля ввода. Для редактирования
    void setServiceName(const QString &serviceName);
    void setSpecialistName(const QString &specialistName);
    void setServiceCost(const QString &serviceCost);
    void setServiceTime(const QString &serviceTime);


private:
    QLineEdit *serviceNameLineEdit; // 4 строки - поля ввода
    QLineEdit *specialistNameLineEdit;
    QLineEdit *serviceCostLineEdit;
    QLineEdit *serviceTimeLineEdit;
    QPushButton *addButton; // добавить и отмена
    QPushButton *cancelButton;
};

#endif // ADDSERVICE_H - конец определения класса
