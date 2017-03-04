/***********************************************************
 * 生成项目选择流程的主窗口
 * 目前所有选择项保存在内存中， 选择完成后能过读取保存的信息开始生成项目
 * [后期考虑把选择的配置放到一个配置文件中]
 *
 * create by MasterFan
 *      on 2017年2月25日10:29:31
 *
 *
 *
 ***********************************************************/

#ifndef DIALOGGENERATEPRO_H
#define DIALOGGENERATEPRO_H

#include <QDialog>
#include <QDebug>
#include <QHash>
#include <QToolButton>

#include <QFileDialog>

#include "bean/WidgetBean.h"
#include "bean/ConfBean.h"
#include "DialogWidgetLists.h"
#include "bean/WidgetToolBean.h"
#include "choose/DialogToolsList.h"


namespace Ui {
class DialogGeneratePro;
}

class DialogGeneratePro : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGeneratePro(QWidget *parent = 0);
    ~DialogGeneratePro();

public:
    enum BaseChoose {
        NotSetProjectName = 0x01,
        NotSetPackageName = 0x02,
        NotSetWorkspace   = 0x03,
        Done              = 0x00
    };

//variables
private:
    Ui::DialogGeneratePro *ui;

    ConfBean *conf;                 //配置信息

    int currentIndex = 0;                  //表示stackedWidget的index;
    QHash<int, QToolButton*> completeHash; //最上面显示四个步骤toolsButton
    DialogWidgetLists* dialogWidgetLists;  //选择widget弹窗
    DialogToolsList*   dialogToolList;     //选择tools弹窗

//functions
private:
    void disableWidget();  //禁用一些控件， 选择没完成时， 完成按钮不可用
    void initialzie();     //一些初始化操作
    bool checkVariableComplete(int index);                 //检查当前步骤是否完成
    void changeButtonState(int completeIndex, int oIndex); //设置按钮完成效果

    int checkCurrentStep(int); ////检查当前步骤是否选择完整


//slots
private slots:
    void onPreviousClicked();   //上一步按钮点击
    void onNextClicked();       //下一步
    void onDoneClicked();       //完成

    void chooseWidgetsByLists();//选择widget
    void chooseToolsByList();   //选择工具

    void receiveChooseList(QList<WidgetToolBean*> dataList); //接收返回widget
    void receiveChooseTools(QList<WidgetToolBean*> dataList);//接收返回tools

    void chooseWorkspace();//选择工作空间目录

    //顶部的toolButton步骤按钮点击slots
    void step1();//第一步
    void step2();
    void step3();
    void step4();

    //测试 database
    void sqliteAdd();
    void sqliteDel();
    void sqliteQuery();
    void sqliteUpdate();
};

#endif // DIALOGGENERATEPRO_H
