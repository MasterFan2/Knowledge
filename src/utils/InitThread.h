#ifndef INITTHREAD_H
#define INITTHREAD_H

#include <QThread>
#include <QDebug>

class InitThread : public QThread
{
    Q_OBJECT
public:
    InitThread(QObject *parent = 0);

    virtual void run();

signals:
    void done();
};

#endif // INITTHREAD_H
