#ifndef DIALOGGENERATEPRO_H
#define DIALOGGENERATEPRO_H

#include <QDialog>
#include <QDebug>
#include <QHash>
#include <QToolButton>

#include "bean/WidgetBean.h"
#include "DialogWidgetLists.h"

namespace Ui {
class DialogGeneratePro;
}

class DialogGeneratePro : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGeneratePro(QWidget *parent = 0);
    ~DialogGeneratePro();

//variables
private:
    Ui::DialogGeneratePro *ui;
    int currentIndex = 0;//表示stackedWidget的index;
    QHash<int, QToolButton*> completeHash;
    DialogWidgetLists* dialogWidgetLists;

//functions
private:
    void checkWidget();  //禁用一些控件， 选择没完成时， 完成按钮不可用
    bool checkVariableComplete(int index);//检查当前步骤是否完成
    void initialzie();   //一些初始化操作
    void changeButtonState(int completeIndex, int oIndex);//设置按钮完成效果


//slots
private slots:
    void onPreviousClicked();//上一步按钮点击
    void onNextClicked();    //下一步
    void onDoneClicked();    //完成

    void chooseWidgetsByLists();//选择保存好的widget

    void receiveChooseList(QList<WidgetBean*> dataList);//接收返回数据

    //test database
    void sqliteAdd();
    void sqliteDel();
    void sqliteQuery();
    void sqliteUpdate();
};

#endif // DIALOGGENERATEPRO_H
