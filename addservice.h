#ifndef ADDSERVICE_H
#define ADDSERVICE_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class AddService : public QDialog
{
    Q_OBJECT

public:
    AddService(QWidget *parent = nullptr);

    QString getServiceName() const;
    QString getSpecialistName() const;
    QString getServiceCost() const;
    QString getServiceTime() const;

private:
    QLineEdit *serviceNameLineEdit;
    QLineEdit *specialistNameLineEdit;
    QLineEdit *serviceCostLineEdit;
    QLineEdit *serviceTimeLineEdit;
    QPushButton *addButton;
    QPushButton *cancelButton;
};

#endif // ADDSERVICE_H
