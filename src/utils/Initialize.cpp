#include "Initialize.h"
#include <QDebug>

Initialize::Initialize(QObject *parent):QThread(parent)
{

}

void Initialize::run()
{
    qDebug() << "Thread run";
    QThread::sleep(5);
    qDebug() << "Thread end";
    emit done();
}
