/*****************************************************************************************
 * 生成项目核心处理流程
 *
 * 01.生成目录结构
 * 02.把配置信息归类，如：把所有权限放到一个变量中，需要copy的文件放到另一个文件中...
 * 03.copy   png、drawable、layout、anim、libs、so、java文件到配置的项目目录中。【不需要修改的】
 *    如：把一些图片coPy到mipmap-hdpi...
 * 04.写入所有颜色到values-->colors.xml中
 * 05.写入dimens.xml
 * 06.写入styles.xml
 * 07.写入attrs.xml
 * 08.写入strings.xml
 * 09.写入配置信息到AndroidManifest.xml中
 * 10.创建app/.gitignore文件、
 * 11.创建app/build.gradle文件
 * 12.创建项目根目录.gitignore文件
 * 13.创建项目根目录build.gradle文件
 * 14.创建项目.iml文件
 *
 * create by MasterFan
 *      on 2017年3月1日 15：42
 *
 *
 *****************************************************************************************/

#include "AndroidKernel.h"
#include <QDir>

AndroidKernel::AndroidKernel()
{
}

/**
 * 生成目录结构
 * 1.${workspace}/${ProjectName}
 * 2.${workspace}/${ProjectName}/app/src/main
 * 3.${workspace}/${ProjectName}/app/src/main/res
 * 4.${workspace}/${ProjectName}/app/src/main/java
 * 5.${workspace}/${ProjectName}/app/src/main/java/${packageName}
 * 6.${workspace}/${ProjectName}/app/src/main/java/${packageName}/bean、ui、widget、utils ...
 * 7.${workspace}/${ProjectName}/app/src/main/res/layout、mipmap-h、x、xx、xxx、m、values、drawable、anim
 * @brief generateStructure
 * @return
 */
int AndroidKernel::generateStructure(ConfBean *conf)        //生成目录结构
{
    //1.${workspace}/${ProjectName}
    QDir dirProject(conf->workspace + conf->applicationName);
    
    //5.${workspace}/${ProjectName}/app/src/main/java/${packageName}
    QDir dirMain(conf->packageName.replace(".", "/"));
    
    
    if (!dirProject.exists())//没有目录
    {
        dirProject.mkdir(conf->workspace + conf->applicationName);
    }
    
    return 0;
}

int AndroidKernel::copyFilesToDestination()   //copy不变的文件到对应目录,如 png、drawable、layout、anim、libs、so、java
{

    return 0;
}

int AndroidKernel::writeColorsToXml()         //写入所有颜色到values-->colors.xml中
{
    return 0;
}

int AndroidKernel::writeDimensToXml()         //写入dimens.xml
{
    return 0;
}

int AndroidKernel::writeStylesToXml()         //写入styles.xml
{
    return 0;
}

int AndroidKernel::writeAttrsToXml()          //写入attrs.xml
{
    return 0;
}

int AndroidKernel::writeStringsToXml()        //写入strings.xml
{
    return 0;
}

int AndroidKernel::createAndroidManifest()    //写入配置信息到AndroidManifest
{
    return 0;
}

int AndroidKernel::createAppGitIgnoreFile()   //创建app/.gitignore文件、
{
    return 0;
}

int AndroidKernel::createAppBuildGradleFile() //创建app/build.gradle文件
{
    return 0;
}

int AndroidKernel::createPROJECTGitIgnore()   //创建项目的git忽略文件
{
    return 0;
}

int AndroidKernel::createPROJECTBuildGradle() //创建项目的Build.Gradle文件
{
    return 0;
}

int AndroidKernel::createPROJECTIml()         //创建项目.iml文件
{
    return 0;
}
