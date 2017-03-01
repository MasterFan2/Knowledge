/***********************************************************
 * 插件、工具的基础属性
 *
 *
 *
 *
 * create by MasterFan
 *      on 2017年3月1日
 *
 *
 *
 ***********************************************************/
#ifndef WIDGETTOOLBEAN_H
#define WIDGETTOOLBEAN_H

#include <QString>
#include <QList>

#include "FileBean.h"

class WidgetToolBean
{
public:
    WidgetToolBean();

public:
    int id;
    QString name;       //中文名称， 如：下拉刷新
    QString className;  //类名， 如：TimeUtils
    QString previewpath;//预览图
    QString gif;        //gif动态图路径，【可能前期不处理该字段， 也就是不用】
    QString description;//描述该控件是做什么的、或有些什么功能
    QString permissions;//用到的权限
    QString example;    //示例代码， 【有可能会考虑把示例代码保存成文件】
    int type;           //类型、0：插件    1：工具
    QString remark;     //备注信息

    QList<FileBean> files;//一个组件的所有依赖的文件列表，组件中可能包含了attr文件， 图片文件等。

};

#endif // WIDGETTOOLBEAN_H
