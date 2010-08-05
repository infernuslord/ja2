#ifndef _VFS_H_
#define _VFS_H_

#include <vfs/Core/Interface/vfs_file_interface.h>
#include <vfs/Core/Interface/vfs_location_interface.h>
#include <vfs/Core/Interface/vfs_iterator_interface.h>
#include <vfs/Core/vfs_vloc.h>
#include <vfs/Core/vfs_vfile.h>

#include <map>

namespace vfs
{
	class CProfileStack;

	class VFS_API CVirtualFileSystem
	{
		typedef std::map<vfs::Path,CVirtualLocation*,vfs::Path::Less> tVFS;

		class CRegularIterator;
		class CMatchingIterator;
	public:
		//template VFS_API class TIterator<vfs::tReadableFile>; // explicit instantiation
		typedef TIterator<vfs::tReadableFile> Iterator;

		~CVirtualFileSystem();

		static CVirtualFileSystem*	getVFS();
		static void					shutdownVFS();

		vfs::CProfileStack*		getProfileStack();

		vfs::CVirtualLocation*	getVirtualLocation(vfs::Path const& sPath, bool bCreate = false);
		bool					addLocation(vfs::IBaseLocation* pLocation, vfs::CVirtualProfile *pProfile);

		bool					fileExists(vfs::Path const& rLocalFilePath, vfs::CVirtualFile::ESearchFile eSF = vfs::CVirtualFile::SF_TOP );
		bool					fileExists(vfs::Path const& rLocalFilePath, std::string const& sProfileName);

		vfs::IBaseFile*			getFile(vfs::Path const& rLocalFilePath, vfs::CVirtualFile::ESearchFile eSF = vfs::CVirtualFile::SF_TOP );
		vfs::IBaseFile*			getFile(vfs::Path const& rLocalFilePath, vfs::String const& sProfileName);

		vfs::tReadableFile*		getReadFile(vfs::Path const& rLocalFilePath, vfs::CVirtualFile::ESearchFile eSF = vfs::CVirtualFile::SF_TOP );
		vfs::tReadableFile*		getReadFile(vfs::Path const& rLocalFilePath, vfs::String const& sProfileName);

		vfs::tWritableFile*		getWriteFile(vfs::Path const& rLocalFilePath, vfs::CVirtualFile::ESearchFile eSF = vfs::CVirtualFile::SF_TOP );
		vfs::tWritableFile*		getWriteFile(vfs::Path const& rLocalFilePath, vfs::String const& sProfileName);

		bool					removeFileFromFS(vfs::Path const& sFilePath);
		bool					removeDirectoryFromFS(vfs::Path const& sDir);
		bool					createNewFile(vfs::Path const& sFileName);

		Iterator				begin();
		Iterator				begin(vfs::Path const& sPattern);
	private:
		vfs::CProfileStack		m_oProfileStack;
		tVFS					m_mapFS;
	private:
		CVirtualFileSystem();
		static CVirtualFileSystem* m_pSingleton;
	};

	VFS_API bool canWrite();
} // end namespace

VFS_API vfs::CVirtualFileSystem*  getVFS();


#endif // _VFS_H_
