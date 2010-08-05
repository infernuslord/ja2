#include <vfs/Aspects/vfs_debugging.h>

static vfs::Aspects::IDebugCallback* s_debug_callback = 0;

vfs::Aspects::IDebugCallback* vfs::Aspects::getDebugCallback()
{
	return s_debug_callback;
}

void vfs::Aspects::setDebugCallback(vfs::Aspects::IDebugCallback* callback)
{
	s_debug_callback = callback;
}

void vfs::Aspects::onError(const wchar_t* error_str)
{
	if(s_debug_callback)
	{
		s_debug_callback->onError(error_str);
	}
}
