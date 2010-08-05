#include <vfs/Aspects/vfs_logging.h>

static vfs::Aspects::ILogger* s_Logger = 0;

void vfs::Aspects::setLogger(vfs::Aspects::ILogger* logger)
{
	s_Logger = logger;
}

vfs::Aspects::ILogger* vfs::Aspects::getLogger()
{
	return s_Logger;
}

void vfs::Aspects::Info(const wchar_t* info_string)
{
	if(s_Logger)
	{
		s_Logger->Info(info_string);
	}
}

void vfs::Aspects::Warning(const wchar_t* warning_string)
{
	if(s_Logger)
	{
		s_Logger->Warning(warning_string);
	}
}

void vfs::Aspects::Error(const wchar_t* error_string)
{
	if(s_Logger)
	{
		s_Logger->Error(error_string);
	}
}

