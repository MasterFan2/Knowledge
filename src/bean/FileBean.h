/***********************************************************
 * 文件基础信息
 *
 *
 *
 * create by MasterFan
 *      on 2017年3月1日
 *
 *
 *
 ***********************************************************/

#ifndef FILEBEAN_H
#define FILEBEAN_H

#include <QString>

class FileBean
{
public:
    FileBean();

public:
    int id;
    QString fileDir;    //文件保存在本地的位置， 生成项目时复制的路径
    QString fileName;   //文件名,如：icon_back.jpg
    QString dirName;    //项目中全名， 如：res/drawable,就是把这个文件拷贝到项目哪个文件夹下
    QString description;//描述这个文件是做什么的， 一个简短描述
};

#endif // FILEBEAN_H
