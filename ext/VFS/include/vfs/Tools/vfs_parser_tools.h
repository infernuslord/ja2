#ifndef _VFS_PARSER_TOOLS_H_
#define _VFS_PARSER_TOOLS_H_

#include <vfs/Core/vfs_types.h>
#include <vfs/Core/Interface/vfs_file_interface.h>

#include <list>

namespace vfs
{
	class VFS_API CReadLine
	{
		static const vfs::size_t BUFFER_SIZE = 1024;
	public:
		CReadLine(vfs::tReadableFile& rFile);
		~CReadLine();

		bool fillBuffer();
		bool fromBuffer(std::string& line);
		bool getLine(std::string& line);
	private:
		vfs::Byte			_buffer[BUFFER_SIZE+1];
		vfs::tReadableFile& _file;
		vfs::size_t			_bytes_left;
		vfs::size_t			_buffer_pos;
		vfs::size_t			_buffer_last;
		bool				_eof;

		void operator=(CReadLine const& rl);
	};

	/**************************************************************/
	/**************************************************************/

	class VFS_API CTokenizer
	{
	public:
		CTokenizer(vfs::String const& str);
		~CTokenizer();

		bool next(vfs::String& token, vfs::String::char_t delimeter = L',');
	private:
		const vfs::String	m_list;
		vfs::String::size_t	m_current, m_next;

		void operator=(CTokenizer const& str);
	};

	VFS_API bool matchPattern(vfs::String const& sPattern, vfs::String const& sStr);
	VFS_API bool matchPattern(vfs::String const& sPattern, vfs::String::str_t const& sStr);

} // namespace vfs

/**************************************************************/
/**************************************************************/

//#define USE_CODE_PAGE

#ifdef USE_CODE_PAGE
class CodePageReader
{
public:
	enum EMode
	{
		Error, Normal, Shift, Ctrl, Alt
	};
	void ReadCodePage(vfs::Path const& codepagefile);
private:
	CodePageReader::EMode ExtractMode(std::string const &readStr, size_t startPos);
	bool ExtractCode(std::string const& str, int iStart, vfs::UInt32& rInsertPoint, vfs::String::str_t& u8s);
};

namespace charSet
{
	enum ECharSet
	{
		CS_SPACE			= 1,
		CS_ALPHA_LC			= 2,
		CS_ALPHA_UC			= 4,
		CS_ALPHA			= CS_ALPHA_LC + CS_ALPHA_UC,
		CS_NUMERIC			= 8,
		CS_ALPHA_NUM		= CS_ALPHA + CS_NUMERIC,
		CS_SPECIAL_ALPHA_LC	= 16,
		CS_SPECIAL_ALPHA_UC	= 32,
		CS_SPECIAL_ALPHA	= CS_SPECIAL_ALPHA_LC + CS_SPECIAL_ALPHA_UC,
		CS_SPECIAL_NON_CHAR	= 65,
	};

	bool IsFromSet(char wc,			unsigned int char_set);
	bool IsFromSet(int wc,			unsigned int char_set);
	bool IsFromSet(unsigned int wc,	unsigned int char_set);
	bool IsFromSet(wchar_t wc,		unsigned int char_set);

	void AddToCharSet(ECharSet eset, std::wstring cset);

	void InitializeCharSets();
};
#endif // USE_CODE_PAGE

#endif // _VFS_PARSER_TOOLS_H_

