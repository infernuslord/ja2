#ifndef _VFS_7Z_LIBRARY_H_
#define _VFS_7Z_LIBRARY_H_

#include <vfs/Core/Location/vfs_uncompressed_lib_base.h>
#include <vfs/Core/File/vfs_lib_file.h>

namespace vfs
{
	class VFS_API CUncompressed7zLibrary : public vfs::CUncompressedLibraryBase
	{
	public:
		CUncompressed7zLibrary(tReadableFile *libraryFile,
			vfs::Path const& mountPoint,
			bool ownFile = false,
			vfs::ObjBlockAllocator<vfs::CLibFile>* allocator=NULL);		
		virtual ~CUncompressed7zLibrary();

		virtual bool init();
	private:
		vfs::ObjBlockAllocator<vfs::CLibFile>* _allocator;
	};
} // end namespace

#endif // _VFS_7Z_LIBRARY_H_

