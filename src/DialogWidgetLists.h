#ifndef DIALOGWIDGETLISTS_H
#define DIALOGWIDGETLISTS_H

#include <QDialog>

namespace Ui {
class DialogWidgetLists;
}

class DialogWidgetLists : public QDialog
{
    Q_OBJECT

public:
    explicit DialogWidgetLists(QWidget *parent = 0);
    ~DialogWidgetLists();

private:
    Ui::DialogWidgetLists *ui;
};

#endif // DIALOGWIDGETLISTS_H
