/***********************************************************
 * 控件 、工具类 实体
 * 包含基础属性和get/set
 * 后期考虑添加数据库操作
 *
 * create by MasterFan
 *      on 2017年2月24日
 *
 *   @deprecate
 *
 ***********************************************************/

#ifndef WIDGETBEAN_H
#define WIDGETBEAN_H

#include <QString>

class WidgetBean
{
private:
    int mId;
    QString mName;
    QString mPath;
    QString mDescription;
    QString mPermisions;
    int mType;
    QString mRemark;

public:
    WidgetBean();

//get
public:
    int id();
    QString name();
    QString path();
    QString description();
    QString permisions();
    int type();
    QString remark();

//set
    void setId(int mId);
    void setName(QString mName);
    void setPath(QString mPath);
    void setDescription(QString mDescription);
    void setPermisions(QString mPermisions);
    void setType(int mType);
    void setRemark(QString mRemark);
};

#endif // WIDGETBEAN_H
