/******************************
 * listWidget 单个item
******************************/
#ifndef ITEMWIDGETLISTFORM_H
#define ITEMWIDGETLISTFORM_H

#include <QWidget>
#include <QCheckBox>

#include <QPixmap>
#include <QMovie>

#include "../bean/WidgetBean.h"

namespace Ui {
class ItemWidgetListForm;
}

class ItemWidgetListForm : public QWidget
{
    Q_OBJECT

public:
    explicit ItemWidgetListForm(QWidget *parent = 0);
    ~ItemWidgetListForm();

    void setUiData(WidgetBean* bean);//设置item的数据

    QCheckBox* checkBox();

private:
    Ui::ItemWidgetListForm *ui;
    QCheckBox* mChkBox;
};

#endif // ITEMWIDGETLISTFORM_H
