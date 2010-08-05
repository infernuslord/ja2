#include <vfs/Aspects/vfs_synchronization.h>

static vfs::Aspects::IMutexFactory* s_mutex_factory = 0;

void vfs::Aspects::setMutexFactory(IMutexFactory* mutex_factory)
{
	s_mutex_factory = mutex_factory;
}
vfs::Aspects::IMutexFactory* vfs::Aspects::getMutexFactory()
{
	return s_mutex_factory;
}


vfs::Aspects::Mutex::Mutex() : _locked(0)
{
	if(s_mutex_factory)
	{
		_mutex = s_mutex_factory->createMutex();
	}
	else
	{
		_mutex = new IMutex();
	}
}

vfs::Aspects::Mutex::~Mutex()
{
	if(_mutex)
	{
		_mutex->unlock();
		delete _mutex;
	}
}

void vfs::Aspects::Mutex::lock()
{
	_mutex->lock();
	_locked++;
}

void vfs::Aspects::Mutex::unlock()
{
	if(_locked > 0)
	{
		_locked--;
		_mutex->unlock();
	}
}
