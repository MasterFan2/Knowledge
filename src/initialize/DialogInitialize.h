/***********************************************************
 * 程序运行前的初始化，主要处理工作如下：
 * 1.生成项目运行过程中用到的一些文件夹
 *  【预览图】【gif动态效果】【java源文件】【res资源文件】【配置文件】
 *
 * 2.数据库创建，表创建
 *
 * create by MasterFan
 *          on 2017年3月7日
 *
 ***********************************************************/
#ifndef DIALOGINITIALIZE_H
#define DIALOGINITIALIZE_H

#include <QDialog>
#include <QMovie>
#include <QStringList>

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
    void createSuccessFile();        //为了方便， 初始化完成后创建一个文件，表示已经初始化过了。
    void createFolders(QStringList); //创建一些资源文件的目录，如：gif/preview

private:
    Ui::DialogInitialize *ui;
    DBUtil* dbUtil;

};

#endif // DIALOGINITIALIZE_H
