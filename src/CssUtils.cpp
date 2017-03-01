/***********************************************************
 * 加载CSS样式工具类
 *
 *
 *
 * create by MasterFan
 *      on 2017年1月23日
 *
 *
 *
 ***********************************************************/

#include "CssUtils.h"

CssUtils::CssUtils()
{

}

QString CssUtils::loadCss(QString fileName)
{
    QFile file(fileName);
    QString str;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
         QByteArray bytes = file.readAll();
         QTextCodec *codec = QTextCodec::codecForName("GBK");
         if(codec)
              str = codec->toUnicode(bytes);
    }
    return str;
}
