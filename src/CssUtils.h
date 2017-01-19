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
