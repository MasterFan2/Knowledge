#ifndef INITIALIZE_H
#define INITIALIZE_H

#include <QThread>

class Initialize : public QThread
{
    Q_OBJECT
public:
    Initialize(QObject *parent = 0);

    void run();

signals:
    void done();
};

#endif // INITIALIZE_H
