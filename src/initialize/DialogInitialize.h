#ifndef DIALOGINITIALIZE_H
#define DIALOGINITIALIZE_H

#include <QDialog>
#include <QMovie>

#include "../utils/DBUtil.h"

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
    DBUtil* dbUtil;

};

#endif // DIALOGINITIALIZE_H
