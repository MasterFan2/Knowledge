#include "ItemWidgetListForm.h"
#include "ui_ItemWidgetListForm.h"

ItemWidgetListForm::ItemWidgetListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemWidgetListForm)
{
    ui->setupUi(this);
}

ItemWidgetListForm::~ItemWidgetListForm()
{
    delete ui;
}
