#ifndef HEADERFORM_H
#define HEADERFORM_H

#include <QWidget>
#include <QFrame>
#include <QMouseEvent>

namespace Ui {
class HeaderForm;
}

class HeaderForm : public QFrame
{
    Q_OBJECT

public:
    explicit HeaderForm(QWidget *parent = 0);
    ~HeaderForm();

private:
    Ui::HeaderForm *ui;

};

#endif // HEADERFORM_H
