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
