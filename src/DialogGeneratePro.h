#ifndef DIALOGGENERATEPRO_H
#define DIALOGGENERATEPRO_H

#include <QDialog>

namespace Ui {
class DialogGeneratePro;
}

class DialogGeneratePro : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGeneratePro(QWidget *parent = 0);
    ~DialogGeneratePro();

private:
    Ui::DialogGeneratePro *ui;
};

#endif // DIALOGGENERATEPRO_H
