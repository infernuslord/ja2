#include <vfs/Core/File/vfs_file.h>
#include <vfs/Core/vfs_debug.h>
#include <vfs/Core/os_functions.h>

#include <vfs/Aspects/vfs_debugging.h>
#include <vfs/Aspects/vfs_settings.h>

#include <sys/stat.h>

#define ERROR_FILE(msg)		BuildString(L"[").add(this->getPath()).add(L"] - ").add(msg).get()

static inline bool hasAttrib(vfs::UInt32 const& attrib, vfs::UInt32 Attribs)
{
	return attrib == (attrib & Attribs);
}

static inline void copyAttributes(vfs::UInt32 osFileAttributes, vfs::UInt32& vfsFileAttributes)
{
	if(os::FileAttributes::ATTRIB_ARCHIVE == (os::FileAttributes::ATTRIB_ARCHIVE & osFileAttributes))
	{
		vfsFileAttributes |= vfs::FileAttributes::ATTRIB_ARCHIVE;
	}
	if(os::FileAttributes::ATTRIB_COMPRESSED == (os::FileAttributes::ATTRIB_COMPRESSED & osFileAttributes))
	{
		vfsFileAttributes |= vfs::FileAttributes::ATTRIB_COMPRESSED;
	}
	if(os::FileAttributes::ATTRIB_DIRECTORY == (os::FileAttributes::ATTRIB_DIRECTORY & osFileAttributes))
	{
		vfsFileAttributes |= vfs::FileAttributes::ATTRIB_DIRECTORY;
	}
	if(os::FileAttributes::ATTRIB_HIDDEN == (os::FileAttributes::ATTRIB_HIDDEN & osFileAttributes))
	{
		vfsFileAttributes |= vfs::FileAttributes::ATTRIB_HIDDEN;
	}
	if(os::FileAttributes::ATTRIB_NORMAL == (os::FileAttributes::ATTRIB_NORMAL & osFileAttributes))
	{
		vfsFileAttributes |= vfs::FileAttributes::ATTRIB_NORMAL;
	}
	if(os::FileAttributes::ATTRIB_OFFLINE == (os::FileAttributes::ATTRIB_OFFLINE & osFileAttributes))
	{
		vfsFileAttributes |= vfs::FileAttributes::ATTRIB_OFFLINE;
	}
	if(os::FileAttributes::ATTRIB_READONLY == (os::FileAttributes::ATTRIB_READONLY & osFileAttributes))
	{
		vfsFileAttributes |= vfs::FileAttributes::ATTRIB_READONLY;
	}
	if(os::FileAttributes::ATTRIB_SYSTEM == (os::FileAttributes::ATTRIB_SYSTEM & osFileAttributes))
	{
		vfsFileAttributes |= vfs::FileAttributes::ATTRIB_SYSTEM;
	}
	if(os::FileAttributes::ATTRIB_TEMPORARY == (os::FileAttributes::ATTRIB_TEMPORARY & osFileAttributes))
	{
		vfsFileAttributes |= vfs::FileAttributes::ATTRIB_TEMPORARY;
	}
}

#ifdef WIN32
	static inline DWORD _seekDir(vfs::IBaseFile::ESeekDir seekDir)
	{
		if(seekDir == vfs::IBaseFile::SD_BEGIN)
		{
			return FILE_BEGIN;
		}
		else if(seekDir == vfs::IBaseFile::SD_CURRENT)
		{
			return FILE_CURRENT;
		}
		else if(seekDir == vfs::IBaseFile::SD_END)
		{
			return FILE_END;
		}
		THROWEXCEPTION(BuildString().add(L"Unknown seek direction [").add(seekDir).add(L"]").get());
	}
#else
	static inline int _seekDir(vfs::IBaseFile::ESeekDir seekDir)
	{
		if(seekDir == vfs::IBaseFile::SD_BEGIN)
		{
			return SEEK_SET;
		}
		else if(seekDir == vfs::IBaseFile::SD_CURRENT)
		{
			return SEEK_CUR;
		}
		else if(seekDir == vfs::IBaseFile::SD_END)
		{
			return SEEK_END;
		}
		THROWEXCEPTION(BuildString().add(L"Unknown seek direction [").add(seekDir).add(L"]").get());
	}
#endif

template<typename WriteType>
vfs::TFile<WriteType>::TFile(vfs::Path const& filename) 
: tBaseClass(filename), m_isOpen_read(false), m_file(0)
{
}

template<typename WriteType>
vfs::TFile<WriteType>::~TFile()
{
	//VFS_LOCK(m_mutex);
#ifndef WIN32
	if(m_file)clearerr(m_file);
#endif
	if(m_isOpen_read)
	{
		this->close();
	}
}

template<typename WriteType>
void vfs::TFile<WriteType>::close()
{
	//VFS_LOCK(m_mutex);
	if(m_file)
	{
#ifdef WIN32
		if(!CloseHandle(m_file))
		{
			DWORD err = GetLastError();
			if(err != NO_ERROR)
			{
				VFS_ON_ERROR(ERROR_FILE(BuildString(L"Could not close file : ").add(err).get()).c_str());
				THROWEXCEPTION(ERROR_FILE(BuildString(L"Could not close file : ").add(err).get()));
			}
		}
#else
		//clearerr(m_file);
		fflush(m_file);
		int error = fclose(m_file);
		if(error)
		{
			//const char* error_str = perror(error);
			VFS_ON_ERROR(ERROR_FILE(BuildString(L"Could not close file : ").add(error).get()).c_str());
			THROWEXCEPTION(ERROR_FILE(BuildString(L"Could not close file : ").add(error).get()));
		}
#endif
		m_file = NULL;
	}
	m_isOpen_read = false;
}

template<typename WriteType>
vfs::FileAttributes vfs::TFile<WriteType>::getAttributes()
{
	//VFS_LOCK(m_mutex);
	vfs::Path fullpath;
	THROWIFFALSE(this->_getRealPath(fullpath), ERROR_FILE(L""));

	vfs::UInt32 osFileAttributes = 0;
	os::FileAttributes fa;
	THROWIFFALSE( fa.getFileAttributes(fullpath, osFileAttributes), ERROR_FILE(L"Could not read file attributes") );

	vfs::UInt32 _attribs = vfs::FileAttributes::ATTRIB_INVALID;
	copyAttributes(osFileAttributes, _attribs);

	if(!this->implementsWritable())
	{
		_attribs &= ~vfs::FileAttributes::ATTRIB_NORMAL;
		_attribs |= vfs::FileAttributes::ATTRIB_READONLY;
	}

	return vfs::FileAttributes(_attribs, vfs::FileAttributes::LT_NONE);
}

template<typename WriteType>
bool vfs::TFile<WriteType>::isOpenRead()
{
	//VFS_LOCK(m_mutex);
	return m_isOpen_read;
}

template<typename WriteType>
bool vfs::TFile<WriteType>::_internalOpenRead(vfs::Path const& path)
{
	//VFS_LOCK(m_mutex);
	if( m_isOpen_read )
		return true;
#ifdef WIN32
	m_file = vfs::Settings::getUseUnicode() ? 
		CreateFileW(path.c_str(),GENERIC_READ,FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL) :
		CreateFileA(vfs::String::narrow(path.c_str(),path.length()).c_str(),GENERIC_READ,FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	DWORD err = GetLastError();
	if(err != NO_ERROR && err != ERROR_ALREADY_EXISTS)
	{
		VFS_ON_ERROR(ERROR_FILE(BuildString(L"Error when opening file : ").add(err).get()).c_str());
		return m_isOpen_read = false;
	}
	return m_isOpen_read = true;
#else
	m_file = fopen(path.to_string().c_str(), "r");
	return m_isOpen_read = (m_file != NULL);
#endif
}

template<typename WriteType>
bool vfs::TFile<WriteType>::openRead()
{
	//VFS_LOCK(m_mutex);
	return _internalOpenRead(this->m_filename);
}

template<typename WriteType>
vfs::size_t vfs::TFile<WriteType>::read(vfs::Byte* pData, vfs::size_t bytesToRead)
{
	//VFS_LOCK(m_mutex);
	THROWIFFALSE( m_isOpen_read, ERROR_FILE(L"file not opened") );
#ifdef WIN32
	DWORD has_read = 0;
	if(!ReadFile(m_file, pData, bytesToRead, &has_read, NULL))
	{
		DWORD err = GetLastError();
		if(err != NO_ERROR && err != ERROR_HANDLE_EOF)
		{
			VFS_ON_ERROR(ERROR_FILE(BuildString(L"read error : ").add(err).get()).c_str());
			THROWEXCEPTION(ERROR_FILE(BuildString(L"read error : ").add(err).get()).c_str());
		}
	}
#else
	size_t has_read = fread(pData,1,bytesToRead,m_file);
	if(has_read != bytesToRead)
	{
		int error = ferror(m_file);
		if(error)
		{
			VFS_ON_ERROR(ERROR_FILE(BuildString(L"read error : ").add(error).get()).c_str());
			THROWEXCEPTION(ERROR_FILE(BuildString(L"read error : ").add(error).get()).c_str());
		}
		clearerr(m_file);
	}
#endif
	return has_read;
}

template<typename WriteType>
vfs::size_t vfs::TFile<WriteType>::getReadPosition()
{
	//VFS_LOCK(m_mutex);
	THROWIFFALSE( m_isOpen_read, ERROR_FILE(L"file not opened") );
#ifdef WIN32
	LARGE_INTEGER current_position,zero;
	zero.QuadPart = 0;
	if(!SetFilePointerEx(m_file, zero, &current_position, FILE_CURRENT))
	{
		DWORD err = GetLastError();
		if(err != NO_ERROR)
		{
			VFS_ON_ERROR(ERROR_FILE(BuildString(L"set position error : ").add(err).get()).c_str());
			THROWEXCEPTION(ERROR_FILE(BuildString(L"set position error : ").add(err).get()));
		}
	}
	return (vfs::size_t)current_position.QuadPart;
#else
	long int pos = ftell(m_file);
	if(pos == -1L)
	{
		int error = ferror(m_file);
		if(error)
		{
			VFS_ON_ERROR(ERROR_FILE(BuildString(L"set position error : ").add(error).get()).c_str());
			THROWEXCEPTION(ERROR_FILE(BuildString(L"set position error : ").add(error).get()));
		}
	}
	return (vfs::size_t)pos;
#endif
}

template<typename WriteType>
void vfs::TFile<WriteType>::setReadPosition(vfs::size_t positionInBytes)
{
	//VFS_LOCK(m_mutex);
	THROWIFFALSE( m_isOpen_read, ERROR_FILE(L"file not opened") );
#ifdef WIN32
	LARGE_INTEGER pos;
	pos.QuadPart = positionInBytes;
	if(!SetFilePointerEx(m_file, pos, NULL, FILE_BEGIN))
	{
		DWORD err = GetLastError();
		if(err != NO_ERROR)
		{
			VFS_ON_ERROR(ERROR_FILE(BuildString(L"set position error : ").add(err).get()).c_str());
			THROWEXCEPTION(ERROR_FILE(BuildString(L"set position error : ").add(err).get()));
		}
	}
#else
	int error = fseek(m_file,positionInBytes,SEEK_SET);
	if(error)
	{
		VFS_ON_ERROR(ERROR_FILE(BuildString(L"set position error : ").add(error).get()).c_str());
		THROWEXCEPTION(ERROR_FILE(BuildString(L"set position error : ").add(error).get()));
	}
#endif
}

template<typename WriteType>
void vfs::TFile<WriteType>::setReadPosition(vfs::offset_t offsetInBytes, IBaseFile::ESeekDir seekDir)
{
	//VFS_LOCK(m_mutex);
	THROWIFFALSE( m_isOpen_read, ERROR_FILE(L"file not opened") );
#ifdef WIN32
	DWORD ioSeekDir;
	TRYCATCH_RETHROW( ioSeekDir = _seekDir(seekDir), ERROR_FILE(L"seek error"));

	LARGE_INTEGER offset;
	offset.QuadPart = offsetInBytes;
	if(!SetFilePointerEx(m_file, offset, NULL, ioSeekDir))
	{
		DWORD err = GetLastError();
		if(err != NO_ERROR)
		{
			VFS_ON_ERROR(ERROR_FILE(BuildString(L"set position error : ").add(err).get()).c_str());
			THROWEXCEPTION(ERROR_FILE(BuildString(L"set position error : ").add(err).get()).c_str());
		}
	}
#else
	int ioSeekDir;
	TRYCATCH_RETHROW( ioSeekDir = _seekDir(seekDir), ERROR_FILE(L"seek error"));
	int error = fseek(m_file, offsetInBytes, ioSeekDir);
	if(error)
	{
		VFS_ON_ERROR(ERROR_FILE(BuildString(L"set position error : ").add(error).get()).c_str());
		THROWEXCEPTION(ERROR_FILE(BuildString(L"set position error : ").add(error).get()).c_str());
	}
#endif
}

/********************************************************************************/
/********************************************************************************/


vfs::CFile::CFile(vfs::Path const& filename) 
: tBaseClass(filename), m_isOpen_write(false)
{
}

vfs::CFile::~CFile()
{
	//VFS_LOCK(m_mutex);
	if(m_isOpen_read || m_isOpen_write)
	{
		this->close();
	}
}

void vfs::CFile::close()
{
	//VFS_LOCK(m_mutex);
	tBaseClass::close();
	m_isOpen_write = false;
}

bool vfs::CFile::deleteFile()
{
	//VFS_LOCK(m_mutex);
	this->close();
	return os::deleteRealFile(m_filename);
}

bool vfs::CFile::isOpenWrite()
{
	//VFS_LOCK(m_mutex);
	return m_isOpen_write;
}

bool vfs::CFile::_internalOpenWrite(vfs::Path const& path, bool createWhenNotExist, bool truncate)
{
	//VFS_LOCK(m_mutex);
	if( m_isOpen_write )
		return true;
#ifdef WIN32
	DWORD Mode = 0;
	if(createWhenNotExist)
	{
		Mode |= OPEN_ALWAYS;
	}
	else
	{
		Mode |= OPEN_EXISTING;
	}
	if(truncate)
	{
		Mode |= TRUNCATE_EXISTING;
	}

	m_file = vfs::Settings::getUseUnicode() ? 
		CreateFileW(path.c_str(),GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,NULL,Mode,FILE_ATTRIBUTE_NORMAL,NULL) :
		CreateFileA(vfs::String::narrow(path.c_str(),path.length()).c_str(),GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,NULL,Mode,FILE_ATTRIBUTE_NORMAL,NULL);
	DWORD err = GetLastError();
	if(truncate && err == ERROR_FILE_NOT_FOUND)
	{
		Mode = CREATE_ALWAYS;
		m_file = vfs::Settings::getUseUnicode() ? 
			CreateFileW(path.c_str(),GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,Mode,FILE_ATTRIBUTE_NORMAL,NULL) :
			CreateFileA(vfs::String::narrow(path.c_str(),path.length()).c_str(),GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,NULL,Mode,FILE_ATTRIBUTE_NORMAL,NULL);
		err = GetLastError();
	}
	if(err != NO_ERROR && err != ERROR_ALREADY_EXISTS)
	{
		VFS_ON_ERROR(BuildString(L"Error when opening file - ").add(path.c_str()).add(L" - [").add(err).add(L"]").get().c_str());
		return m_isOpen_write = false;
	}
	return m_isOpen_write = true;
#else
	m_file = fopen(path.to_string().c_str(), "r+");
	if( (!m_file && createWhenNotExist) || (m_file && truncate))
	{
		m_file = fopen(path.to_string().c_str(), "w");
	}

	return m_isOpen_write = (m_file != NULL);
#endif
}

bool vfs::CFile::openWrite(bool createWhenNotExist, bool truncate)
{
	//VFS_LOCK(m_mutex);
	return _internalOpenWrite(m_filename, createWhenNotExist, truncate);
}

vfs::size_t vfs::CFile::write(const vfs::Byte* data, vfs::size_t bytesToWrite)
{
	//VFS_LOCK(m_mutex);
	THROWIFFALSE( m_isOpen_write, ERROR_FILE(L"file not opened") );
#ifdef WIN32
	DWORD has_written = 0;
	if(!WriteFile(m_file, data, bytesToWrite, &has_written, NULL))
	{
		DWORD err = GetLastError();
		if(err != NO_ERROR)
		{
			VFS_ON_ERROR(BuildString(L"write error : ").add(err).get().c_str());
			THROWEXCEPTION(BuildString(L"write error : ").add(err).get());
		}
	}
#else
	size_t has_written = fwrite(data, 1, bytesToWrite, m_file);
	if(has_written != bytesToWrite)
	{
		int error = ferror(m_file);
		if(error)
		{
			VFS_ON_ERROR(BuildString(L"write error : ").add(error).get().c_str());
			THROWEXCEPTION(BuildString(L"write error : ").add(error).get());
		}
	}

#endif
	return (vfs::size_t)has_written;
}	

vfs::size_t vfs::CFile::getWritePosition()
{
	//VFS_LOCK(m_mutex);
	THROWIFFALSE( m_isOpen_write, ERROR_FILE(L"file not opened") );
#ifdef WIN32
	LARGE_INTEGER current_position, zero;
	zero.QuadPart = 0;
	if(!SetFilePointerEx(m_file, zero, &current_position, FILE_CURRENT))
	{
		DWORD err = GetLastError();
		if(err != NO_ERROR)
		{
			VFS_ON_ERROR(ERROR_FILE(BuildString(L"set position error : ").add(err).get()).c_str());
			THROWEXCEPTION(ERROR_FILE(BuildString(L"set position error : ").add(err).get()));
		}
	}
	return (vfs::size_t)current_position.QuadPart;
#else
	long int pos = ftell(m_file);
	if(pos == -1L)
	{
		int error = ferror(m_file);
		if(error)
		{
			VFS_ON_ERROR(ERROR_FILE(BuildString(L"set position error : ").add(error).get()).c_str());
			THROWEXCEPTION(ERROR_FILE(BuildString(L"set position error : ").add(error).get()));
		}
	}
	return (vfs::size_t)pos;
#endif
}

void vfs::CFile::setWritePosition(vfs::size_t positionInBytes)
{
	//VFS_LOCK(m_mutex);
	THROWIFFALSE( m_isOpen_write, ERROR_FILE(L"file not opened") );
#ifdef WIN32
	LARGE_INTEGER pos;
	pos.QuadPart = positionInBytes;
	if(!SetFilePointerEx(m_file, pos, NULL, FILE_CURRENT))
	{
		DWORD err = GetLastError();
		if(err != NO_ERROR)
		{
			VFS_ON_ERROR(ERROR_FILE(BuildString(L"set position error : ").add(err).get()).c_str());
			THROWEXCEPTION(ERROR_FILE(BuildString(L"set position error : ").add(err).get()));
		}
	}
#else
	int error = fseek(m_file,positionInBytes,SEEK_SET);
	if(error)
	{
		VFS_ON_ERROR(ERROR_FILE(BuildString(L"set position error : ").add(error).get()).c_str());
		THROWEXCEPTION(ERROR_FILE(BuildString(L"set position error : ").add(error).get()));
	}
#endif
}

void vfs::CFile::setWritePosition(vfs::offset_t offsetInBytes, vfs::IBaseFile::ESeekDir seekDir)
{
	//VFS_LOCK(m_mutex);
	THROWIFFALSE( m_isOpen_write, ERROR_FILE(L"file not opened") );
#ifdef WIN32
	DWORD ioSeekDir;
	TRYCATCH_RETHROW( ioSeekDir = _seekDir(seekDir), ERROR_FILE(L"seek error"));

	LARGE_INTEGER offset;
	offset.QuadPart = offsetInBytes;
	if(!SetFilePointerEx(m_file, offset, NULL, ioSeekDir))
	{
		DWORD err = GetLastError();
		if(err != NO_ERROR)
		{
			VFS_ON_ERROR(ERROR_FILE(BuildString(L"set position error : ").add(err).get()).c_str());
			THROWEXCEPTION(ERROR_FILE(BuildString(L"set position error : ").add(err).get()));
		}
	}
#else
	int ioSeekDir;
	TRYCATCH_RETHROW( ioSeekDir = _seekDir(seekDir), ERROR_FILE(L"seek error"));
	int error = fseek(m_file, offsetInBytes, ioSeekDir);
	if(error)
	{
		VFS_ON_ERROR(ERROR_FILE(BuildString(L"set position error : ").add(error).get()).c_str());
		THROWEXCEPTION(ERROR_FILE(BuildString(L"set position error : ").add(error).get()).c_str());
	}
#endif
}

template<typename T>
vfs::size_t vfs::TFile<T>::getSize()
{
	//VFS_LOCK(m_mutex);
#ifdef WIN32
	bool was_open = false;
	if(m_file)
	{
		was_open = true;
	}
	else
	{
		THROWIFFALSE(this->openRead(),ERROR_FILE(L"could not open file"));
	}
	vfs::size_t size;
#	ifdef _MSC_VER
		LARGE_INTEGER li_size;
		if(!GetFileSizeEx(m_file, &li_size))
		{
			DWORD err = GetLastError();
			if(err != NO_ERROR)
			{
				VFS_ON_ERROR(ERROR_FILE(BuildString(L"get size error : ").add(err).get()).c_str());
				THROWEXCEPTION(ERROR_FILE(BuildString(L"get size error : ").add(err).get()));
			}
		}
		size = (vfs::size_t)li_size.QuadPart;
#	else
		DWORD low_part, high_part;
		low_part = GetFileSize(m_file, &high_part);
		if(low_part == INVALID_FILE_SIZE)
		{
			DWORD err = GetLastError();
			if(err != NO_ERROR)
			{
				VFS_ON_ERROR(ERROR_FILE(BuildString(L"get size error : ").add(err).get()).c_str());
				THROWEXCEPTION(ERROR_FILE(BuildString(L"get size error : ").add(err).get()));
			}
		}
		size = low_part;
#	endif
	if(!was_open)
	{
		this->close();
	}
	return size;
#else
	// if file was alredy opened, keep it open, otherwise close it
	bool closeAtExit = !m_isOpen_read;

	THROWIFFALSE( m_isOpen_read || this->openRead(), ERROR_FILE(L"could not open file") )

	// save current position 
	long int current_position = ftell(m_file);

	// move to end of the file
	fseek(m_file, 0, SEEK_END);
	long int file_size = ftell(m_file);

	// move to old position
	fseek(m_file, current_position, SEEK_SET);
	THROWIFFALSE(current_position == ftell(m_file), ERROR_FILE(L"could not restore seek position"));

	if(closeAtExit)
	{
		this->close();
	}
	return (vfs::size_t)file_size;
#endif
}

/******************************************************************/
/******************************************************************/

template class vfs::TFile<vfs::IWriteType>;

