#include <vfs/Core/vfs_init.h>
#include <vfs/Core/vfs.h>
#include <vfs/Core/File/vfs_file.h>
#include <vfs/Core/File/vfs_memory_file.h>
#include <vfs/Core/Location/vfs_directory_tree.h>
#include <vfs/Ext/slf/vfs_slf_library.h>
#include <vfs/Ext/7z/vfs_7z_library.h>
#include <vfs/Ext/7z/vfs_create_7z_library.h>

#include <vfs/Tools/vfs_property_container.h>
#include <vfs/Tools/vfs_log.h>

#include <vfs/Aspects/vfs_logging.h>
#include <vfs/Aspects/vfs_debugging.h>
#include <vfs/Aspects/vfs_settings.h>

/////////////////////////////////

vfs_init::Location::Location()
: m_optional(false)
{
};

/////////////////////////////////

vfs_init::Profile::Profile()
: m_writable(false)
{
};

vfs_init::Profile::~Profile()
{
	t_locations::iterator it = locations.begin();
	for(;it != locations.end(); ++it)
	{
		if(it->first) delete it->second;
	}
	locations.clear();
}

void vfs_init::Profile::addLocation(Location* loc, bool own)
{
	locations.push_back(std::make_pair(own,loc));
}

/////////////////////////////////

vfs_init::VfsConfig::~VfsConfig()
{
	t_profiles::iterator it = profiles.begin();
	for(;it != profiles.end(); ++it)
	{
		if(it->first) delete it->second;
	}
}

void vfs_init::VfsConfig::addProfile(Profile* prof, bool own)
{
	profiles.push_back(std::make_pair(own,prof));
}

void vfs_init::VfsConfig::appendConfig(VfsConfig& conf)
{
	VfsConfig::t_profiles::iterator it = conf.profiles.begin();
	for(; it != conf.profiles.end(); ++it)
	{
		// even if the other object owns its profiles, this one does not
		profiles.push_back(std::make_pair(false,it->second));
	}
}

/********************************************************************/
/********************************************************************/

bool vfs_init::initVirtualFileSystem(vfs::Path const& vfs_ini)
{
	std::list<vfs::Path> li;
	li.push_back(vfs_ini);
	return initVirtualFileSystem(li);
}
bool vfs_init::initVirtualFileSystem(std::list<vfs::Path> const& vfs_ini_list)
{
	vfs::PropertyContainer oVFSProps;
	std::list<vfs::Path>::const_iterator clit = vfs_ini_list.begin();
	for(; clit != vfs_ini_list.end(); ++clit)
	{
		oVFSProps.initFromIniFile(*clit);
	}
	return initVirtualFileSystem(oVFSProps);
}
bool vfs_init::initVirtualFileSystem(vfs::PropertyContainer& oVFSProps)
{
	VFS_LOG_INFO(L"Processing VFS configuration");
	vfs_init::VfsConfig conf;

	std::list<vfs::String> lProfiles, lLocSections;

	oVFSProps.getStringListProperty(L"vfs_config",L"PROFILES",lProfiles,L"");
	if(lProfiles.empty())
	{
		VFS_LOG_ERROR(L"no profiles specified");
		VFS_ON_ERROR(L"no profiles specified");
		return false;
	}
	
	std::list<vfs::String>::const_iterator prof_cit = lProfiles.begin();
	for(; prof_cit != lProfiles.end(); ++prof_cit)
	{
		vfs::String sProfSection = vfs::String("PROFILE_") + vfs::String(*prof_cit);

		vfs_init::Profile *prof = new vfs_init::Profile();
		prof->m_name = oVFSProps.getStringProperty(sProfSection,L"NAME",L"");
		prof->m_root = oVFSProps.getStringProperty(sProfSection,L"PROFILE_ROOT",L"");
		prof->m_writable = oVFSProps.getBoolProperty(sProfSection,L"WRITE",false);

		lLocSections.clear();
		oVFSProps.getStringListProperty(sProfSection,L"LOCATIONS",lLocSections,L"");

		std::list<vfs::String>::iterator loc_it = lLocSections.begin();
		for(; loc_it != lLocSections.end(); ++loc_it)
		{
			vfs::String sLocSection = vfs::String("LOC_") + vfs::String(*loc_it);
	
			vfs_init::Location *loc = new vfs_init::Location();
			loc->m_path = oVFSProps.getStringProperty(sLocSection,L"PATH",L"");
			loc->m_vfs_path = oVFSProps.getStringProperty(sLocSection,L"VFS_PATH",L"");
			loc->m_mount_point = oVFSProps.getStringProperty(sLocSection,L"MOUNT_POINT",L"");
			loc->m_type = oVFSProps.getStringProperty(sLocSection,L"TYPE",L"NOT_FOUND");
			loc->m_optional = oVFSProps.getBoolProperty(sLocSection,L"OPTIONAL",false);

			prof->addLocation(loc,true);
		}
		conf.addProfile(prof,true);
	}
	return initVirtualFileSystem(conf);
}

bool vfs_init::initWriteProfile(vfs::CVirtualProfile &rProf)
{
	typedef vfs::TDirectory<vfs::IWritable> tWDir;
	tWDir *pDir = NULL;
	vfs::IBaseLocation *pLoc = rProf.getLocation(vfs::Path(vfs::Const::EMPTY()));
	if(pLoc)
	{
		pDir = dynamic_cast<tWDir*>(pLoc);
	}
	else
	{
		vfs::CDirectoryTree *pDirTree = NULL;
		pDirTree = new vfs::CDirectoryTree(vfs::Path(vfs::Const::EMPTY()),rProf.cRoot);
		if(!pDirTree->init())
		{
			return false;
		}
		TRYCATCH_RETHROW( rProf.addLocation(pDirTree), L"" );
		getVFS()->addLocation(pDirTree, &rProf);
		pDir = pDirTree;
	}
	return pDir != NULL;
}


bool vfs_init::initVirtualFileSystem(vfs_init::VfsConfig const& conf)
{
	VFS_LOG_INFO(L"Initializing Virtual File System");

	vfs::CVirtualFileSystem *pVFS = getVFS();

	if(conf.profiles.empty())
	{
		return false;
	}
	vfs_init::VfsConfig::t_profiles::const_iterator prof_it = conf.profiles.begin();
	for(; prof_it != conf.profiles.end(); ++prof_it)
	{
		vfs_init::Profile* prof = prof_it->second;
		VFS_LOG_INFO(BuildString(L"  Reading profile : ").add(prof->m_name).get().c_str());

		vfs::Path profileRoot = prof->m_root;

		bool bIsWritable = prof->m_writable;

		vfs::CProfileStack *pPS = pVFS->getProfileStack();
		vfs::CVirtualProfile *pProf = pPS->getProfile(prof->m_name);
		if(!pProf)
		{
			pProf = new vfs::CVirtualProfile(prof->m_name, profileRoot, bIsWritable);
			pPS->pushProfile(pProf);
		}
		else
		{
			THROWIFFALSE(pProf->cWritable == bIsWritable, L"profile already exists, but their write properties differ");
			THROWIFFALSE(pProf->cRoot == profileRoot, L"profile already exists, but their root directories differ");
			continue;
		}


		vfs_init::Profile::t_locations::iterator loc_it = prof->locations.begin();
		loc_it = prof->locations.begin();
		for(; loc_it != prof->locations.end(); ++loc_it)
		{
			vfs_init::Location *loc = loc_it->second;

			bool bOptional = loc->m_optional;
			if(vfs::StrCmp::Equal(loc->m_type,L"LIBRARY"))
			{
				vfs::tReadableFile *pLibFile = NULL;
				bool bOwnFile = false;

				vfs::Path fullpath = profileRoot + loc->m_path;
				VFS_LOG_INFO( BuildString(L"    library : \"").add(fullpath).add(L"\"").get().c_str() );

				if(!loc->m_path.empty())
				{
					// try regular file
					pLibFile = vfs::tReadableFile::cast( new vfs::CFile(fullpath) );
					bOwnFile = true;
				}
				if(!pLibFile && !loc->m_vfs_path.empty())
				{
					// if regular file doesn't exist, try to find it in the (partially initialized) VFS
					pLibFile = pVFS->getReadFile(profileRoot + loc->m_vfs_path);
				}
				if(pLibFile)
				{
					vfs::String full_str = pLibFile->getName()();
					vfs::String ext = full_str.c_wcs().substr(full_str.length()-3,3);
					vfs::ILibrary *pLib = NULL;
					if(vfs::StrCmp::Equal(ext,L"slf"))
					{
						pLib = new vfs::CSLFLibrary( pLibFile, loc->m_mount_point );
					}
					else if(vfs::StrCmp::Equal(ext,L".7z"))
					{
						pLib = new vfs::CUncompressed7zLibrary( pLibFile, loc->m_mount_point );
					}
					else
					{
						BuildString bs = BuildString(L"File [").add(loc->m_path).add(L"] in not an SLF or 7z library");
						VFS_LOG_ERROR(bs.get().c_str());
						THROWEXCEPTION(bs.get());
					}
					if(!pLib->init())
					{
						if(!bOptional)
						{
							VFS_LOG_ERROR(L"Could not initialize library");
							THROWEXCEPTION(
								BuildString(L"Could not initialize library [").add(
								loc->m_path).add(L" ]").add(
								L" in : profile [ ").add(prof->m_name).add(L" ],").add(
								L" path [ ").add(fullpath).add(L" ]").get());
						}
					}
					else
					{
						pProf->addLocation(pLib);
						pVFS->addLocation(vfs::tReadLocation::cast(pLib), pProf);
					}
				}
				else
				{
					VFS_LOG_ERROR(BuildString(L"File not found : ").add(loc->m_path).get().c_str());
					THROWEXCEPTION(BuildString(L"File not found : ").add(loc->m_path).get());
				}
			}
			else if(vfs::StrCmp::Equal(loc->m_type,L"DIRECTORY"))
			{
				vfs::Path fullpath = profileRoot + loc->m_path;
				VFS_LOG_INFO( BuildString(L"    directory : \"").add(fullpath).add(L"\"").get().c_str() );

				vfs::IBaseLocation *pDirLocation = NULL;
				bool init_success = false;
				if(bIsWritable)
				{
					vfs::CDirectoryTree *pDirTree = new vfs::CDirectoryTree(loc->m_mount_point, fullpath);
					init_success = pDirTree->init();
					pDirLocation = pDirTree;
				}
				else
				{
					vfs::CReadOnlyDirectoryTree *pDirTree = new vfs::CReadOnlyDirectoryTree(loc->m_mount_point, fullpath);
					init_success = pDirTree->init();
					pDirLocation = pDirTree;
				}
				if(!init_success)
				{
					VFS_LOG_ERROR(L"Could not initialize directory");
					THROWEXCEPTION(
						BuildString(L"Could not initialize directory [\"").add(loc->m_path).add(L"\"]").add(
						L" in : profile [\"").add(prof->m_name).add(L"\"],").add(
						L" path [\"").add(fullpath).add(L"\"]").get());
				}
				else
				{
					pProf->addLocation(pDirLocation);
					pVFS->addLocation(pDirLocation, pProf);
				}
			}
		}
		if(bIsWritable)
		{
			vfs::CProfileStack *pPS = pVFS->getProfileStack();
			vfs::CVirtualProfile *pProf = pPS->getProfile(prof->m_name);
			if(!pProf)
			{
				pProf = new vfs::CVirtualProfile(prof->m_name,profileRoot,true);
				pPS->pushProfile(pProf);
			}
			else if(!pProf->cWritable)
			{
				BuildString bs = BuildString(L"Profile [").add(prof->m_name).add(L"] is supposed to be writable!");
				VFS_LOG_ERROR(bs.get().c_str());
				THROWEXCEPTION(bs.get());
			}
			initWriteProfile(*pProf);
		}
	}

	return true;
}

