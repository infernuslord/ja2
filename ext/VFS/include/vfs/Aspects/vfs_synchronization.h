#ifndef VFS_SYNCHRONIZATION_H
#define VFS_SYNCHRONIZATION_H

#include <vfs/vfs_config.h>

namespace vfs
{
	namespace Aspects
	{
		class IMutex
		{
		public:
			virtual void lock() {};
			virtual void unlock() {};
		};

		class IMutexFactory
		{
		public:
			virtual IMutex* createMutex() = 0;
		};

		VFS_API void setMutexFactory(IMutexFactory* mutex_factory);
		VFS_API IMutexFactory* getMutexFactory();

		class Mutex
		{
		public:
			Mutex();
			~Mutex();

			void lock();
			void unlock();
		private:
			int		_locked;
			IMutex* _mutex;
		};

		class ScopedLock
		{
		public:
			ScopedLock(Mutex& mutex) : _mutex(mutex) {
				this->_mutex.lock();
			}
			~ScopedLock(){
				this->_mutex.unlock();
			}
		private:
			Mutex&	_mutex;
		};
	}
}

#ifdef VFS_SYNCHRONIZE
#	if !defined VFS_LOCK
#		define VFS_LOCK(mutex) vfs::Aspects::ScopedLock _scoped_lock(mutex)
#	endif
#else
#	if !defined VFS_LOCK
#		define VFS_LOCK(mutex) 
#	endif
#endif

#endif // VFS_SYNCHRONIZATION_H
