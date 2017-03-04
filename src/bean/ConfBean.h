/***********************************************************
 * 项目的所有配置读取到这个实例中
 *
 * 包含基础属性和get/set
 *
 *
 * create by MasterFan
 *      on 2017年3月1日
 *
 *
 *
 ***********************************************************/

#ifndef CONFBEAN_H
#define CONFBEAN_H

#include <QString>
#include <QList>

#include "WidgetToolBean.h"

class ConfBean
{
public:
    ConfBean();

public:

    //step 1 基本配置
    QString applicationName;//项目名称
    QString packageName;    //包名：e.g:com.master.fan
    QString workspace;      //项目路径

    //step 2 版本选择
    QString minimunVersion; //最低支持版本
    QString toolsBuild;     //gradle版本号
    QString targetVersion;  //目标版本
    int compileSdkVersion;  //编译版本
    QString buildToolsVersion;//编译工具版本号
    bool hasLibSo;          //是否有so库，true:写入jniLibs.srcDirs=['libs'] 或是创建jniLib目录

    //step3 组件选择
    QList<WidgetToolBean*> widgetList;

    //step 4工具类选择
    QList<WidgetToolBean*> toolList;
};

#endif // CONFBEAN_H
