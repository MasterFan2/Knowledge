/***********************************************************
 * 程序主入口
 *
 *
 *
 * create by MasterFan
 *      on 2017年1月25日
 *
 *
 *
 ***********************************************************/

#include "src/MainWindow.h"
#include "src/HeaderForm.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/images/res/1484816114_Know.ico"));

    MainWindow w;
    w.show();

//    HeaderForm headerForm;
//    headerForm.show();

    return a.exec();
}
