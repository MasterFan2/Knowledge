#include "InitThread.h"

InitThread::InitThread(QObject *parent):QThread(parent)
{

}

void InitThread::run()
{
    qDebug() << "begin";
    QThread::sleep(5);
    qDebug() << "Thread end ";

    emit done();
}
