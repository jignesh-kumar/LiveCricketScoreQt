#include "mythread.h"
#include "qdebug.h"

MyThread::MyThread(QThread *parent) : QThread(parent)
{

}

MyThread::~MyThread()
{

}

void MyThread::run()
{
    while(1)
    {
        MyThread::sleep(10);
        emit timeToDownload();
    }
}

