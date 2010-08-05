#ifndef VFS_DEBUGGING_H
#define VFS_DEBUGGING_H

#include <vfs/vfs_config.h>

namespace vfs
{
	namespace Aspects
	{
		class IDebugCallback
		{
		public:
			virtual void onError(const wchar_t* error_str) = 0;
		};

		VFS_API void setDebugCallback(IDebugCallback *callback);
		VFS_API IDebugCallback* getDebugCallback();

		void onError(const wchar_t* error_str);
	}
}

#if !defined VFS_ON_ERROR
#	define VFS_ON_ERROR(str)	vfs::Aspects::onError(str);
#endif

#endif // VFS_DEBUGGING_H
