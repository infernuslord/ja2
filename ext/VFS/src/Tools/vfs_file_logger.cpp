#include <vfs/Tools/vfs_file_logger.h>

vfs::FileLogger::FileLogger(vfs::Path const& log_file, bool append, vfs::Log::EFlushMode flush_mode)
: m_log( *vfs::Log::create(log_file, append, flush_mode) )
{
	m_log.Register();
	m_clock.startTimer();
}

vfs::FileLogger::FileLogger(vfs::tWritableFile* file, bool append, vfs::Log::EFlushMode flush_mode)
: m_log( *vfs::Log::create(file,append, flush_mode) ) 
{
	m_log.Register();
	m_clock.startTimer();
}


vfs::FileLogger::~FileLogger()
{
	m_log.destroy();
}

void vfs::FileLogger::Info(const wchar_t* info_str)
{
	m_log << "[" << m_clock.running() << "] : " << vfs::String::as_utf8(info_str) << vfs::Log::endl;
}

void vfs::FileLogger::Warning(const wchar_t* warning_str)
{
	m_log << "[" << m_clock.running() << "] : " << vfs::String::as_utf8(warning_str) << vfs::Log::endl;
}

void vfs::FileLogger::Error(const wchar_t* error_str)
{
	m_log << "[" << m_clock.running() << "] : " << vfs::String::as_utf8(error_str) << vfs::Log::endl;
}

void vfs::FileLogger::Info(vfs::String const& info_str)
{
	this->Info(info_str.c_str());
}
void vfs::FileLogger::Warning(vfs::String const& warning_str)
{
	this->Warning(warning_str.c_str());
}
void vfs::FileLogger::Error(vfs::String const& error_str)
{
	this->Error(error_str.c_str());
}
