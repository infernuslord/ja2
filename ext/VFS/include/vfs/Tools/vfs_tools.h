#ifndef _VFS_TOOLS_H_
#define _VFS_TOOLS_H_

#include <vfs/vfs_config.h>

#include <vfs/Core/vfs_types.h>
#include <list>

namespace vfs
{
	template<typename CharType, typename ValueType>
	std::basic_string<CharType> toString(ValueType const& rVal) 
	{
		std::basic_stringstream<CharType> tss;
		if( !(tss << std::fixed << rVal))
		{
			return std::basic_string<CharType>();
		}
		return tss.str();
	}

	template<typename T_>
	bool convertTo(vfs::String const& sStr, T_ &rVal)
	{
		std::wstringstream ss;
		ss.str(sStr.c_wcs());
		if(!(ss >> rVal))
		{
			return false;
		}
		return true;
	}

	template<typename T_>
	vfs::String toStringList(std::list<T_> const& rValList)
	{
		std::wstringstream ss;
		typename std::list<T_>::const_iterator cit = rValList.begin();
		if(cit != rValList.end())
		{
			ss << *cit;
			cit++;
			for(;cit != rValList.end(); ++cit)
			{
				ss << L" , " << *cit;
			}
		}
		if(!ss)
		{
			return L"";
		}
		return ss.str();
	}

	template<>
	VFS_API vfs::String toStringList<vfs::String>(std::list<vfs::String> const& rValList);

	////////////////////////////////////////////////////////////////////////////////////////////

	// remove leading and trailing white characters;
	template<typename StringType>
	VFS_API StringType trimString(StringType const& sStr, vfs::size_t iMinPos, vfs::size_t iMaxPos);

	// explicit instantiations : std::string, std::wstring, vfs::String
	template<>
	VFS_API std::string trimString<std::string>(std::string const& sStr, vfs::size_t iMinPos, vfs::size_t iMaxPos);

	template<>
	VFS_API std::wstring trimString<std::wstring>(std::wstring const& sStr, vfs::size_t iMinPos, vfs::size_t iMaxPos);

	template<>
	VFS_API vfs::String trimString<vfs::String>(vfs::String const& sStr, vfs::size_t iMinPos, vfs::size_t iMaxPos);


} // namespace vfs

#endif // _TOOLS_H_
