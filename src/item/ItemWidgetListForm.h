#ifndef ITEMWIDGETLISTFORM_H
#define ITEMWIDGETLISTFORM_H

#include <QWidget>

namespace Ui {
class ItemWidgetListForm;
}

class ItemWidgetListForm : public QWidget
{
    Q_OBJECT

public:
    explicit ItemWidgetListForm(QWidget *parent = 0);
    ~ItemWidgetListForm();

private:
    Ui::ItemWidgetListForm *ui;
};

#endif // ITEMWIDGETLISTFORM_H
