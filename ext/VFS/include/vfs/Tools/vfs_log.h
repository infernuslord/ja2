#ifndef _VFS_LOG_H_
#define _VFS_LOG_H_

#include <vfs/Core/vfs_types.h>
#include <vfs/Core/vfs_file_raii.h>
#include <vfs/Core/File/vfs_file.h>
#include <vfs/Core/Interface/vfs_file_interface.h>
#include <vfs/Tools/vfs_tools.h>
#include <vfs/Aspects/vfs_synchronization.h>

namespace vfs
{
	class VFS_API IRefCountable
	{
	public:
		IRefCountable() : _ref_count(1) {}
		virtual ~IRefCountable() {}

		virtual void Delete() = 0;

		void Register() {
			_ref_count++;
		}
		void UnRegister() {
			_ref_count--;
			if(_ref_count <= 0){
				delete this;
			}
		}
	private:
		int _ref_count;
	};

	class VFS_API Log : public IRefCountable
	{
	public:
		enum EFlushMode
		{
			FLUSH_ON_DELETE,
			FLUSH_ON_ENDL,
			FLUSH_BUFFER,
			FLUSH_IMMEDIATELY,
		};
		enum _endl{endl};
	public:

		Log(vfs::Path const& fileName, bool use_vfs_file, bool append = false, EFlushMode flushMode = FLUSH_ON_DELETE);
		Log(vfs::tWritableFile* file, bool append = false, EFlushMode flushMode = FLUSH_ON_DELETE);
		virtual ~Log();

		virtual void	Delete();

		// don't explicitely call destroy if you haven't explicitely created the object
		void			destroy();

		static Log*		create(vfs::Path const& fileName, bool append = false, EFlushMode flushMode = FLUSH_ON_DELETE);
		static Log*		create(vfs::tWritableFile* file, bool append = false, EFlushMode flushMode = FLUSH_ON_DELETE);
		static void		flushRelease();
		static void		flushDelete();

		static vfs::String const&	getSharedString();
		static void					setSharedString(vfs::String const& str);

		Log& operator<<(vfs::UInt64 const& t);
		Log& operator<<(vfs::UInt32 const& t);
		Log& operator<<(vfs::UInt16 const& t);
		Log& operator<<(vfs::UInt8 const& t);

		Log& operator<<(vfs::Int64 const& t);
		Log& operator<<(vfs::Int32 const& t);
		Log& operator<<(vfs::Int16 const& t);
		Log& operator<<(vfs::Int8  const& t);

#ifdef _MSC_VER
		Log& operator<<(DWORD const& t);
#endif
		Log& operator<<(float const& t);
		Log& operator<<(double const& t);

		Log& operator<<(const char* t);
		Log& operator<<(const wchar_t* t);
		Log& operator<<(std::string const& t);
		Log& operator<<(std::wstring const& t);
		Log& operator<<(vfs::String const& t);

		Log& operator<<(void* const& t);

		Log& operator<<(vfs::Log::_endl const& endl);

		void setAppend(bool append = true);
		void setBufferSize(vfs::UInt32 bufferSize);

		void flush();

		void lock();
		void unlock();
	private:
		void _test_flush(bool force=false);

		template<typename T_>
		Log& pushNumber(T_ const& t)
		{
			_buffer << toString<char>(t);
			_buffer_size += sizeof(T_);
			_test_flush();
			return *this;
		}
	private:
		vfs::Path				_filename;
		vfs::tWritableFile*		_file;
		bool					_own_file;
		bool					_first_write;
		EFlushMode				_flush_mode;
		bool					_append;
		::size_t				_buffer_size, _buffer_test_size;
		std::stringstream		_buffer;

		vfs::Aspects::Mutex		_mutex;
	private:
		static std::list<Log*>& _logs();
		static vfs::String		_shared_id_str;
	};
} // end namespace vfs

#endif // _VFS_LOG_H_
