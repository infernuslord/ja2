#include <vfs/Tools/vfs_log.h>
#include <cstring>

#ifdef WIN32
static const char ENDL[] = "\r\n";
#else
static const char ENDL[] = "\n";
#endif

std::list<vfs::Log*>& vfs::Log::_logs()
{
	static std::list<vfs::Log*> logs;
	return logs;
}

vfs::Log* vfs::Log::create(vfs::Path const& fileName, bool append, EFlushMode flushMode)
{
	_logs().push_back(new vfs::Log(fileName, true, append, flushMode));
	return _logs().back();
}
vfs::Log* vfs::Log::create(vfs::tWritableFile* file, bool append, EFlushMode flushMode)
{
	_logs().push_back(new vfs::Log(file, append, flushMode));
	return _logs().back();
}

void vfs::Log::flushDelete()
{
	std::list<vfs::Log*>::iterator it = _logs().begin();
	for(; it != _logs().end(); ++it)
	{
		(*it)->flush();
		(*it)->Delete();
	}
	_logs().clear();
}

void vfs::Log::flushRelease()
{
	std::list<vfs::Log*>::iterator it = _logs().begin();
	for(; it != _logs().end(); ++it)
	{
		(*it)->flush();
		(*it)->_file = NULL;
	}
}

vfs::String vfs::Log::_shared_id_str;

vfs::String const& vfs::Log::getSharedString()
{
	return _shared_id_str;
}

void vfs::Log::setSharedString(vfs::String const& str)
{
	_shared_id_str = str;
}


vfs::Log::Log(vfs::Path const& fileName, bool use_vfs_file, bool append, EFlushMode flushMode)
:	IRefCountable(),
	_filename(fileName), _file(NULL), _own_file(false),
	_first_write(true), _flush_mode(flushMode), _append(append),
	_buffer_size(0), _buffer_test_size(512)
{};

vfs::Log::Log(vfs::tWritableFile* file, bool append, EFlushMode flushMode)
:	IRefCountable(),
	_file(file), _own_file(false),
	_first_write(true), _flush_mode(flushMode), _append(append),
	_buffer_size(0), _buffer_test_size(512)
{
}


vfs::Log::~Log()
{
	_test_flush(true);
	if(_file && _own_file)
	{
		delete _file;
	}
}

void vfs::Log::Delete()
{
	this->UnRegister();
}


void vfs::Log::destroy()
{
	VFS_LOCK(_mutex);
	this->flush();
	this->Delete();
	_logs().remove(this);
}


vfs::Log& vfs::Log::operator<<(vfs::UInt64 const& t)
{
	VFS_LOCK(_mutex);
	return pushNumber(t);
}
vfs::Log& vfs::Log::operator<<(vfs::UInt32 const& t)
{
	VFS_LOCK(_mutex);
	return pushNumber(t);
}
vfs::Log& vfs::Log::operator<<(vfs::UInt16 const& t)
{
	VFS_LOCK(_mutex);
	return pushNumber(t);
}
vfs::Log& vfs::Log::operator<<(vfs::UInt8 const& t)
{
	VFS_LOCK(_mutex);
	return pushNumber(t);
}

vfs::Log& vfs::Log::operator<<(vfs::Int64 const& t)
{
	VFS_LOCK(_mutex);
	return pushNumber(t);
}
vfs::Log& vfs::Log::operator<<(vfs::Int32 const& t)
{
	VFS_LOCK(_mutex);
	return pushNumber(t);
}
vfs::Log& vfs::Log::operator<<(vfs::Int16 const& t)
{
	VFS_LOCK(_mutex);
	return pushNumber(t);
}
vfs::Log& vfs::Log::operator<<(vfs::Int8 const& t)
{
	VFS_LOCK(_mutex);
	return pushNumber(t);
}
#ifdef _MSC_VER
	vfs::Log& vfs::Log::operator<<(DWORD const& t)
	{
		VFS_LOCK(_mutex);
		return pushNumber(t);
	}
#endif
vfs::Log& vfs::Log::operator<<(float const& t)
{
	VFS_LOCK(_mutex);
	return pushNumber(t);
}
vfs::Log& vfs::Log::operator<<(double const& t)
{
	VFS_LOCK(_mutex);
	return pushNumber(t);
}

vfs::Log& vfs::Log::operator<<(const char* t)
{
	VFS_LOCK(_mutex);
	_buffer << t;
	_buffer_size += strlen(t);
	_test_flush();
	return *this;
}
vfs::Log& vfs::Log::operator<<(const wchar_t* t)
{
	VFS_LOCK(_mutex);
	std::string s = vfs::String::as_utf8(t);
	_buffer << s;
	_buffer_size += s.length();
	_test_flush();
	return *this;
}
vfs::Log& vfs::Log::operator<<(std::string const& t)
{
	VFS_LOCK(_mutex);
	_buffer << t;
	_buffer_size += t.length();
	_test_flush();
	return *this;
}
vfs::Log& vfs::Log::operator<<(std::wstring const& t)
{
	VFS_LOCK(_mutex);
	std::string s = vfs::String::as_utf8(t);
	_buffer << s;
	_buffer_size += s.length();
	_test_flush();
	return *this;
}
vfs::Log& vfs::Log::operator<<(vfs::String const& t)
{
	VFS_LOCK(_mutex);
	std::string s = t.utf8();
	_buffer << s;
	_buffer_size += s.length();
	_test_flush();
	return *this;
}

vfs::Log& vfs::Log::operator<<(void* const& t)
{
	VFS_LOCK(_mutex);
	_buffer << t;
	return *this;
}

vfs::Log& vfs::Log::operator<<(vfs::Log::_endl const& endl)
{
	VFS_LOCK(_mutex);
	_buffer << ENDL;
	_buffer_size += sizeof(ENDL)-1;
	if(_flush_mode == vfs::Log::FLUSH_ON_ENDL) flush();
	return *this;
}

/*
vfs::Log& vfs::Log::endl()
{
	_buffer << ENDL;
	_buffer_size += sizeof(ENDL)-1;
	_test_flush();
	return *this;
}
*/
void vfs::Log::setAppend(bool append)
{
	VFS_LOCK(_mutex);
	_append = append;
}

void vfs::Log::setBufferSize(vfs::UInt32 bufferSize)
{
	VFS_LOCK(_mutex);
	_buffer_test_size = bufferSize;
}

void vfs::Log::_test_flush(bool force)
{
	if( (_flush_mode == FLUSH_IMMEDIATELY) || 
		(_flush_mode == FLUSH_BUFFER && _buffer_size > _buffer_test_size) || 
		(/*_flush_mode == FLUSH_ON_DELETE &&*/ force == true) )
	{
		flush();
	}
}

#include <ctime>
#include <vfs/Core/vfs.h>

void vfs::Log::flush()
{
	VFS_LOCK(_mutex);
	::size_t buflen = _buffer.str().length();
	if(buflen == 0)
	{
		return;
	}

	if(!_file)
	{
		THROWIFFALSE(!_filename.empty(), L"_file is NULL and _filename is empty");
		//vfs::CVirtualProfile *prof = getVFS()->getProfileStack()->topProfile();
		//if( prof && prof->cWritable )
		if(vfs::canWrite())
		{
			try
			{
				vfs::COpenWriteFile file_raii(_filename,true,!_append);
				_file = &file_raii.file();
				file_raii.release();
				_own_file = false;
			}
			catch(...)
			{
			}
		}
		else
		{
			try
			{
				_file = vfs::tWritableFile::cast(new vfs::CFile(_filename));
				_file->openWrite(true,!_append);
				_own_file = true;
			}
			catch(...)
			{
			}
		}
	}

	vfs::COpenWriteFile wfile(_file);
	if(_append)
	{
		wfile->setWritePosition(0,vfs::IBaseFile::SD_END);
	}

	if(_first_write)
	{
		time_t rawtime;
		time ( &rawtime );
		std::string datetime(ctime(&rawtime));
		std::string s_out;
	
		vfs::size_t wloc = wfile->getWritePosition();
		if(wloc > 0)
		{
			s_out = ENDL;
		}
		s_out += " *** ";
		s_out += datetime.substr(0,datetime.length()-1);
		s_out += " *** ";
		s_out += ENDL;
		s_out += "[ ";
		s_out += _shared_id_str.utf8();
		s_out += " ]";
		s_out += ENDL;
		s_out += ENDL;

		wfile->write(s_out.c_str(), s_out.length());
		_first_write = false;
	}

	wfile->write(_buffer.str().c_str(), buflen);
	_buffer.str("");
	_buffer.clear();
	_buffer_size = 0;

	_append = true;
}

void vfs::Log::lock()
{
	_mutex.lock();
}
void vfs::Log::unlock()
{
	_mutex.unlock();
}
