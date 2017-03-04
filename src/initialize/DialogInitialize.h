#ifndef DIALOGINITIALIZE_H
#define DIALOGINITIALIZE_H

#include <QDialog>
#include <QMovie>

namespace Ui {
class DialogInitialize;
}

class DialogInitialize : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInitialize(QWidget *parent = 0);
    ~DialogInitialize();

private:
    Ui::DialogInitialize *ui;
};

#endif // DIALOGINITIALIZE_H
