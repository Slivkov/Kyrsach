#include "addservice.h"
#include <QVBoxLayout>
#include <QFormLayout>

AddService::AddService(QWidget *parent) // конструктор
    : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QFormLayout *formLayout = new QFormLayout(); // создаю форму для ввода новой услуги
    serviceNameLineEdit = new QLineEdit(this);
    specialistNameLineEdit = new QLineEdit(this);
    serviceCostLineEdit = new QLineEdit(this);
    serviceTimeLineEdit = new QLineEdit(this);

    formLayout->addRow("Название услуги:", serviceNameLineEdit);
    formLayout->addRow("Наименование специалиста:", specialistNameLineEdit);
    formLayout->addRow("Стоимость услуги:", serviceCostLineEdit);
    formLayout->addRow("Время оказания услуги (минут):", serviceTimeLineEdit);

    layout->addLayout(formLayout);
// кнопки добавить и отмена
    addButton = new QPushButton("Добавить", this);
    connect(addButton, &QPushButton::clicked, this, &QDialog::accept);

    cancelButton = new QPushButton("Отмена", this);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    QHBoxLayout *buttonLayout = new QHBoxLayout(); //размещение кнопок на форме
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(cancelButton);

    layout->addLayout(buttonLayout);
}

QString AddService::getServiceName() const // получаю данные все
{
    return serviceNameLineEdit->text();
}

QString AddService::getSpecialistName() const
{
    return specialistNameLineEdit->text();
}

QString AddService::getServiceCost() const
{
    return serviceCostLineEdit->text();
}

QString AddService::getServiceTime() const
{
    return serviceTimeLineEdit->text();
}
