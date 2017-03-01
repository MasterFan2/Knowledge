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

#ifndef CSSUTILS_H
#define CSSUTILS_H
#include <QString>
#include <QFile>
#include <QIODevice>
#include <QTextCodec>

class CssUtils
{
public:
    CssUtils();
    QString loadCss(QString fileName);
};

#endif // CSSUTILS_H
