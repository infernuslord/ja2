#ifndef VFS_LOGGING_H
#define VFS_LOGGING_H

#include <vfs/vfs_config.h>

namespace vfs
{
	namespace Aspects
	{
		class ILogger
		{
		public:
			virtual void Info(const wchar_t* info_string) = 0;
			virtual void Warning(const wchar_t* warning_string) = 0;
			virtual void Error(const wchar_t* error_string) = 0;
		};

		VFS_API void setLogger(ILogger* logger);
		VFS_API ILogger* getLogger();

		void Info(const wchar_t* info_string);
		void Warning(const wchar_t* warning_string);
		void Error(const wchar_t* error_string);
	};
};

#if !defined VFS_LOG_INFO
#	define VFS_LOG_INFO(info)		(vfs::Aspects::Info(info))
#endif

#if !defined VFS_LOG_WARNING
#	define VFS_LOG_WARNING(warning)	(vfs::Aspects::Warning(warning))
#endif

#if !defined VFS_LOG_ERROR
#	define VFS_LOG_ERROR(error)		(vfs::Aspects::Error(error))
#endif

#endif // VFS_LOGGING_H
