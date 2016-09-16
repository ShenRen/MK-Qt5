#ifndef SINGLETON_H
#define SINGLETON_H

#include <QObject>
#include <QSystemSemaphore>
#include <QSharedMemory>

class Singleton
{
public:
    Singleton(const QString&);
    ~Singleton();

    bool running();
    bool launch();
    void release();
    QString makeHash(const QString&, const QString&);
    
private:
    Q_DISABLE_COPY(Singleton)
    const QString key;
    const QString memLockKey;
    const QString sharedmemKey;

    QSharedMemory sharedMem;
    QSystemSemaphore memLock;
};


#endif 