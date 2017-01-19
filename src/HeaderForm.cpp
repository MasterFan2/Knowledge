#include "HeaderForm.h"
#include "ui_HeaderForm.h"

HeaderForm::HeaderForm(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::HeaderForm)
{
    ui->setupUi(this);

//    this->setStyleSheet("QWidget[whatsThis='content'] {background-color:white}");
}

HeaderForm::~HeaderForm()
{
    delete ui;
}
