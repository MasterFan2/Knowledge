#include "DialogWidgetLists.h"
#include "ui_DialogWidgetLists.h"

DialogWidgetLists::DialogWidgetLists(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogWidgetLists)
{
    ui->setupUi(this);
}

DialogWidgetLists::~DialogWidgetLists()
{
    delete ui;
}
