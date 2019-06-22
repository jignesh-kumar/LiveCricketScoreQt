#ifndef MYTHREAD_H
#define MYTHREAD_H

#include "qthread.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QThread *parent = 0);
    ~MyThread();
    void run();

signals:
    void timeToDownload();

public slots:
};

#endif // MYTHREAD_H
