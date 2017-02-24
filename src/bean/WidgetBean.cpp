#include "WidgetBean.h"

WidgetBean::WidgetBean()
{

}

int WidgetBean::id()
{
    return mId;
}

QString WidgetBean::name()
{
    return mName;
}

QString WidgetBean::path()
{
    return mPath;
}

QString WidgetBean::description()
{
    return mDescription;
}

QString WidgetBean::permisions()
{
    return mPermisions;
}

int WidgetBean::type()
{
    return mType;
}

QString WidgetBean::remark()
{
    return mRemark;
}

//set
void WidgetBean::setId(int mId)
{
    this->mId = mId;
}

void WidgetBean::setPath(QString mPath)
{
    this->mPath = mPath;
}

void WidgetBean::setName(QString mName)
{
    this->mName = mName;
}

void WidgetBean::setDescription(QString mDescription)
{
    this->mDescription = mDescription;
}

void WidgetBean::setPermisions(QString mPermisions)
{
    this->mPermisions = mPermisions;
}

void WidgetBean::setRemark(QString mRemark)
{
    this->mRemark = mRemark;
}

void WidgetBean::setType(int mType)
{
    this->mType = mType;
}
