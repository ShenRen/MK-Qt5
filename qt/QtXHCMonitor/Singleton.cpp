#include "Singleton.h"

#include <QCryptographicHash>

Singleton::Singleton(const QString& keyString )
    : key(keyString)
    , memLockKey(makeHash(key, "_memLockKey"))
    , sharedmemKey(makeHash(key, "_sharedmemKey"))
    , sharedMem( sharedmemKey )
    , memLock( memLockKey, 1 )
{
    memLock.acquire();
        {
        QSharedMemory fix( sharedmemKey ); 
        fix.attach();
        }
    memLock.release();
}

Singleton::~Singleton()
{
    release();
}

bool Singleton::running()
{
bool ret;

    if ( sharedMem.isAttached() )
        return false;

    memLock.acquire();
    if((ret = sharedMem.attach()))
        sharedMem.detach();
    memLock.release();

    return ret;
}

bool Singleton::launch()
{
bool ret;

    if(running())
        return false;

    memLock.acquire();
    ret = sharedMem.create(sizeof(quint64));
    memLock.release();
    if(!ret)
        {
        release();
        return false;
        }

    return true;
}

void Singleton::release()
{
    memLock.acquire();
    if ( sharedMem.isAttached() )
        sharedMem.detach();
    memLock.release();
}

QString Singleton::makeHash(const QString& key, const QString& salt)
{
    QByteArray data;

    data.append( key.toUtf8() );
    data.append( salt.toUtf8() );
    data = QCryptographicHash::hash( data, QCryptographicHash::Sha1 ).toHex();

    return data;
}