#include "RWLock_POSIX.h"


namespace Common {


RWLockImpl::RWLockImpl()
{
	if (pthread_rwlock_init(&_rwl, NULL))
		throw ("cannot create reader/writer lock");
}


RWLockImpl::~RWLockImpl()
{
	pthread_rwlock_destroy(&_rwl);
}


} // namespace Utils
