#ifndef _VFS_INIT_H_
#define _VFS_INIT_H_

#include <vfs/Core/vfs_types.h>
#include <vfs/Core/vfs_profile.h>
#include <vfs/Tools/vfs_property_container.h>

namespace vfs_init
{
	class VFS_API Location
	{
	public:
		Location();

		bool		m_optional;
		vfs::String	m_type;
		vfs::Path	m_path, m_vfs_path;
		vfs::Path	m_mount_point;
	};

	class VFS_API Profile
	{
	public:
		Profile();
		~Profile();

		void addLocation(Location* loc, bool own = false);

		////////////////////////////////////////////////
		typedef std::list<std::pair<bool,Location*> > t_locations;
		t_locations locations;

		vfs::String	m_name;
		vfs::Path	m_root;
		bool		m_writable;
	};

	class VFS_API VfsConfig
	{
	public:
		typedef std::list<std::pair<bool,Profile*> > t_profiles;
		~VfsConfig();

		t_profiles profiles;
		void addProfile(Profile* prof, bool own = false);
		void appendConfig(VfsConfig& conf);
	};

	////////////////////////////////////////////////////////////////////////////

	VFS_API bool initWriteProfile(vfs::CVirtualProfile &rProf);

	VFS_API bool initVirtualFileSystem(vfs::Path const& vfs_ini);
	VFS_API bool initVirtualFileSystem(std::list<vfs::Path> const& vfs_ini_list);
	VFS_API bool initVirtualFileSystem(vfs::PropertyContainer& props);
	VFS_API bool initVirtualFileSystem(vfs_init::VfsConfig const& conf);
};

#endif // _VFS_INIT_H_
