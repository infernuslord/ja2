#ifndef _VFS_FILE_LOGGER_H_
#define _VFS_FILE_LOGGER_H_

#include <vfs/Core/vfs_path.h>
#include <vfs/Tools/vfs_log.h>
#include <vfs/Tools/vfs_hp_timer.h>
#include <vfs/Aspects/vfs_logging.h>

namespace vfs
{
	class VFS_API FileLogger : public vfs::Aspects::ILogger
	{
	public:
		FileLogger(vfs::Path const& log_file, bool append = false, vfs::Log::EFlushMode flush_mode = vfs::Log::FLUSH_ON_ENDL);
		FileLogger(vfs::tWritableFile* file, bool append = false, vfs::Log::EFlushMode flush_mode = vfs::Log::FLUSH_ON_ENDL);
		~FileLogger();

		virtual void Info(const wchar_t* info_str);
		virtual void Warning(const wchar_t* warning_str);
		virtual void Error(const wchar_t* error_str);

		void Info(vfs::String const& info_str);
		void Warning(vfs::String const& warning_str);
		void Error(vfs::String const& error_str);
	private:
		Log&		m_log;
		HPTimer	m_clock;
	};
}

#endif // _VFS_FILE_LOGGER_H_
