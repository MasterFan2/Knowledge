#include "DialogGeneratePro.h"
#include "ui_DialogGeneratePro.h"

DialogGeneratePro::DialogGeneratePro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGeneratePro)
{
    ui->setupUi(this);
}

DialogGeneratePro::~DialogGeneratePro()
{
    delete ui;
}
