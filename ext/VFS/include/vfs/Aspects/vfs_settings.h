#ifndef _VFS_SETTIGNS_H_
#define _VFS_SETTIGNS_H_

#include <vfs/vfs_config.h>

namespace vfs
{
	class VFS_API Settings
	{
	public:
		static void setUseUnicode(bool useUnicode);
		static bool getUseUnicode();
	};
}

#endif // _VFS_SETTIGNS_H_
