#include <vfs/Tools/vfs_tools.h>

template<>
vfs::String vfs::toStringList<vfs::String>(std::list<vfs::String> const& rValList)
{
	std::wstringstream ss;
	std::list<vfs::String>::const_iterator cit = rValList.begin();
	if(cit != rValList.end())
	{
		ss << (*cit);
		cit++;
		for(;cit != rValList.end(); ++cit)
		{
			ss << L" , " << (*cit);
		}
	}
	if(!ss)
	{
		return L"";
	}
	return ss.str();
}

/*************************************************************************************/
/*************************************************************************************/

template<>
std::string vfs::trimString<std::string>(std::string const& sStr, vfs::size_t iMinPos, vfs::size_t iMaxPos)
{
	if(iMinPos > iMaxPos || iMaxPos == vfs::npos)
	{
		return "";
	}
	::size_t iStart,iEnd;
	iStart = sStr.find_first_not_of(" \t\r\n",(::size_t)iMinPos);
	iEnd   = sStr.find_last_not_of(" \t\r\n",(::size_t)iMaxPos);
	if( (iStart != std::string::npos) && (iEnd != std::string::npos) )
	{
		return sStr.substr(iStart,iEnd-iStart+1);
	}
	return "";
}
template<>
std::wstring vfs::trimString<std::wstring>(std::wstring const& sStr, vfs::size_t iMinPos, vfs::size_t iMaxPos)
{
	if(iMinPos > iMaxPos || iMaxPos == vfs::npos)
	{
		return L"";
	}
	::size_t iStart,iEnd;
	iStart = sStr.find_first_not_of(L" \t\r\n",(::size_t)iMinPos);
	iEnd   = sStr.find_last_not_of(L" \t\r\n",(::size_t)iMaxPos);
	if( (iStart != std::wstring::npos) && (iEnd != std::wstring::npos) )
	{
		return sStr.substr(iStart,iEnd-iStart+1);
	}
	return L"";
}
template<>
vfs::String vfs::trimString<vfs::String>(vfs::String const& sStr, vfs::size_t iMinPos, vfs::size_t iMaxPos)
{
	return vfs::trimString(sStr.c_wcs(), iMinPos, iMaxPos);
}
