#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMouseEvent>
#include "CssUtils.h"
#include "MFLabel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


//-----------variable------------
private:
    Ui::MainWindow *ui;
    QSystemTrayIcon trayIcon;//托盘

    bool dragging;//窗口移动
    QPoint startPosition;
    QPoint framePosition;

    CssUtils cssLoader;//样式加载工具类

    int lastPosition = -1;//记录上次选中项

    MFLabel *createLabel; //创建项目标签
    MFLabel *minimunLabel;//最小化
    MFLabel *closeLabel;  //最大化

//-----------end variable--------


//------------function-----------
//mouse/close event, tray
private:
    int initSystemTrayIcon();
    void closeEvent(QCloseEvent *event);//关闭事件

    //mouse event
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *event);

    int checkByLastPosition(int position);

    int connectAction();//连接信号， 槽

    int initialize();//初始化

    void addMFLabel();//添加几个可点击的label标签【最小化， 关闭， 生成项目】

//------------function-----------


//------------slots-----------
private slots:
    int onSystemTrayClicked(QSystemTrayIcon::ActivationReason);//托盘点击

    //----托盘的右键菜单点击----
    int onTrayActionExit();
    int onTrayActionLogin();
    int onTrayActionOpen();

    //-------主功能按钮--------
    int onGenProClicked();
    int onConfigClicked();
    int onAddWidgetClicked();
    int onAboutClicked();

    //-------最小化， 最大化--------
    int onMinimunClicked();
    int onCloseClicked();

    //-------生成按钮-----------
    int onGenLabelClicked();

//----------end slots--------

};

#endif // MAINWINDOW_H
