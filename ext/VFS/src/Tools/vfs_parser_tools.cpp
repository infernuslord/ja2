#include <vfs/Core/vfs.h>
#include <vfs/Core/File/vfs_file.h>
#include <vfs/Core/vfs_file_raii.h>
#include <vfs/Tools/vfs_parser_tools.h>
#include <vfs/Tools/vfs_tools.h>

#include <cstring>

/*************************************************************************************/
/*************************************************************************************/

vfs::CReadLine::CReadLine(vfs::tReadableFile& rFile)
: _file(rFile), _buffer_pos(0), _eof(false)
{
	memset(_buffer,0,sizeof(_buffer));

	vfs::COpenReadFile rfile(&_file);
	_bytes_left = rfile->getSize();
	fillBuffer();
	vfs::UByte utf8bom[3] = {0xef,0xbb,0xbf};
	if(memcmp(utf8bom, &_buffer[0],3) == 0)
	{
		_buffer_pos += 3;
	}
	rfile.release();
};

vfs::CReadLine::~CReadLine()
{
	if(_file.isOpenRead())
	{
		_file.close();
	}
}

bool vfs::CReadLine::fillBuffer()
{
	if(_eof)
	{
		return false;
	}
	vfs::size_t bytesRead = BUFFER_SIZE < _bytes_left ? BUFFER_SIZE : _bytes_left;
	try
	{
		vfs::COpenReadFile rfile(&_file);

		// fill the buffer from the start, BUFFER_SIZE charactes at max (_buffer has BUFFER_SIZE+1 elements)
		THROWIFFALSE(bytesRead == _file.read(&_buffer[0], bytesRead), L"");
		rfile.release();
	}
	catch(CBasicException& ex)
	{
		RETHROWEXCEPTION(L"", &ex);
	}

	_bytes_left -= bytesRead;
	_eof = (_bytes_left == 0);


	// bite-wise read files usually terminate a line with \n (or \r\n on WIN32)
	// line-wise read files just returns 0-terminated string

	// always terminate the string with 0
	_buffer[bytesRead] = 0;

	_buffer_pos = 0;
	_buffer_last = bytesRead;

	return true;
}

bool vfs::CReadLine::fromBuffer(std::string& line)
{
	bool done = false;
	while(!done)
	{
		if(_buffer_pos < _buffer_last)
		{
			// start where we left last time
			vfs::Byte *temp = &_buffer[_buffer_pos];
			vfs::size_t start_pos = _buffer_pos;
			// go until we hit 0. since our buffer is always 0 terminated, the second test should be redundant.
			while(*temp && (_buffer_pos < _buffer_last))
			{
				// stop when we find a line terminator
				if(*temp == '\n' || *temp == '\r' /* || *temp == '\0' */)
				{
					break;
				}
				temp++;
				_buffer_pos++;
			}
			// need to append substring, as we might have refilles the buffer (because there was no \n or \r\n terminator)
			line.append( (char*)&_buffer[start_pos], _buffer_pos - start_pos );

			// if we reach the (real) end of the buffer (that always terminate with 0), this means
			// that there was no line terminator and that we have to refill the buffer.
			if( _buffer_pos < BUFFER_SIZE && (*temp == '\n' || *temp == '\r' || *temp == 0) )
			{
				// found the line terminator
				if(*temp == '\r')
				{
					// the \r is most probably followed by \n. 'swallow' both characters
					*temp++;
					_buffer_pos++;
					if( (_buffer_pos < BUFFER_SIZE) && (*temp == '\n' || *temp == 0) )
					{
						// increase buffer position, so that we can start with a valid character in the next run
						_buffer_pos++;
						return true;
					}
					else
					{
						done = !fillBuffer();
					}
				}
				else if(*temp == '\n' || *temp == 0)
				{
					// increase buffer position, so that we can start with a valid character in the next run
					_buffer_pos++;
					return true;
				}
			}
			else
			{
				done = !fillBuffer();
			}
		}
		else
		{
			done = !fillBuffer();
		}
	}
	return false;
}

bool vfs::CReadLine::getLine(std::string& line)
{
	line.clear();
	return fromBuffer(line);
}

/*************************************************************************************/
/*************************************************************************************/

vfs::CTokenizer::CTokenizer(vfs::String const& str)
: m_list(str), m_current(0), m_next(0)
{};

vfs::CTokenizer::~CTokenizer()
{};

bool vfs::CTokenizer::next(vfs::String& token, vfs::String::char_t delimeter)
{
	if(m_next != vfs::String::str_t::npos)
	{
		m_next = m_list.c_wcs().find_first_of(delimeter, m_current);
		if(m_next != vfs::String::str_t::npos)
		{
			token.r_wcs().assign(vfs::trimString(m_list,m_current,m_next > m_current ? m_next-1 : m_current).c_wcs());
			m_current = m_next+1;
		}
		else
		{
			// last or only entry
			token.r_wcs().assign(vfs::trimString(m_list,m_current,m_list.length()).c_wcs());
		}
		return true;
	}
	return false;
}

/*************************************************************************************/
/*************************************************************************************/

/**
 *  try to recursively match the pattern
 */
bool vfs::matchPattern(vfs::String const& sPattern, vfs::String const& sStr)
{
	return matchPattern(sPattern,sStr.c_wcs());
}

bool vfs::matchPattern(vfs::String const& sPattern, vfs::String::str_t const& sStr)
{
	vfs::String::str_t const& pat = sPattern.c_wcs();

	vfs::String::size_t star = pat.find_first_of(vfs::Const::STAR());
	if(star == vfs::String::str_t::npos)
	{
		return vfs::StrCmp::Equal( pat, sStr );
	}
	else if(star == 0)
	{
		if(pat.length() == 1)
		{
			// there is only the '*' -> matches all strings
			return true;
		}
		vfs::String::char_t atpos1 = pat.at(1);
		vfs::String::size_t match = vfs::String::size_t(-1);
		do
		{
			match = sStr.find_first_of(atpos1,match+1);
			if(match == vfs::String::str_t::npos)
			{
				return false;
			}
		} while(!matchPattern( pat.substr(1,pat.length()-1), sStr.substr(match,sStr.length()-match) ));
		return true;
	}
	else // if(star > 0)
	{
		// check if characters before * match
		if(!vfs::StrCmp::Equal(pat.substr(0,star), sStr.substr(0,star)) )
		{
			return false;
		}
		return matchPattern( pat.substr(star,pat.length()-star), sStr.substr(star,sStr.length()-star) );
	}
}

/*************************************************************************************/
/*************************************************************************************/

#ifdef USE_CODE_PAGE

typedef vfs::UInt16 UINT16;
extern UINT16 gsKeyTranslationTable[1024];

CodePageReader::EMode CodePageReader::extractMode(std::string const &readStr, size_t startPos)
{
	vfs::Int32 iEqual = readStr.find_first_of("=",startPos);
	if(iEqual < 0)
	{
		return Error;
	}
	// extract keyword
	std::string key = vfs::trimString(readStr,0,iEqual-1);
	if(!StrCmp::Equal(key, "mode"))
	{
		return Error;
	}
	// extract mode
	EMode mode = Error;
	std::string sMode = vfs::trimString(readStr,iEqual+1,readStr.size());
	if(StrCmp::Equal(sMode, "normal"))
	{
		mode = Normal;
	}
	else if(StrCmp::Equal(sMode, "shift"))
	{
		mode = Shift;
	}
	else if(StrCmp::Equal(sMode, "ctrl"))
	{
		mode = Ctrl;
	}
	else if(StrCmp::Equal(sMode, "alt"))
	{
		mode = Alt;
	}
	return mode;
}

bool CodePageReader::extractCode(std::string const& str, int iStart, vfs::UInt32& rInsertPoint, vfs::String::str_t& u8s)
{
	vfs::Int32 iEqual = str.find_first_of("=",iStart);
	if(iEqual < 0)
	{
		return false;
	}
	// extract insert point
	std::string sip = vfs::TrimString(str,0,iEqual-1);
	if(!ConvertTo<vfs::UInt32>(sip, rInsertPoint))
	{
		return false;
	}
	vfs::String::str_t u8temp;
	IGNOREEXCEPTION(vfs::String::as_utf16(str.substr(iEqual, str.length()-iEqual), u8temp));

	vfs::Int32 iCodeStart, iCodeEnd;
	iCodeStart = u8temp.find_first_of(L"{", 0);
	if(iCodeStart < 0)
	{
		return false;
	}
	iCodeEnd = u8temp.find_last_of(L"}");
	if(iCodeEnd < 0)
	{
		return false;
	}
	u8s = u8temp.substr(iCodeStart+1, iCodeEnd-iCodeStart-1);
	return true;
}

void CodePageReader::readCodePage(vfs::Path const& codepagefile)
{
	if(!GetVFS()->fileExists(codepagefile))
	{
		return;
	}
	vfs::COpenReadFile rfile(codepagefile);
	CReadLine rline(rfile.file());
	std::string sBuffer;
	vfs::UInt32 line_counter = 0;
	EMode mode = Normal;
	while(rline.GetLine(sBuffer))
	{
		line_counter++;
		// very simple parsing : key = value
		if(!sBuffer.empty())
		{
			// remove leading white spaces
			int iStart = sBuffer.find_first_not_of(" \t",0);
			char first = sBuffer.at(iStart);
			switch(first)
			{
			case '!':
			case ';':
			case '#':
				// comment -> do nothing
				break;
			case 'm':
				mode = ExtractMode(sBuffer,iStart);
				if(mode == Error)
				{
					vfs::String::str_t u8s;
					IGNOREEXCEPTION(vfs::String::as_utf16(sBuffer, u8s));
					std::wstringstream wss;
					wss << L"Could not determine mode from line [" << line_counter << L"] : " << u8s;
					THROWEXCEPTION(wss.str().c_str());
				}
				break;
			default:
				vfs::String::str_t u8s;
				vfs::UInt32 uiInsertPoint;
				if(!ExtractCode(sBuffer, iStart,uiInsertPoint,u8s))
				{
					continue;
				}
				if(mode == Shift) uiInsertPoint += 256;
				else if(mode == Ctrl) uiInsertPoint += 512;
				else if(mode == Alt) uiInsertPoint += 768;

				if(uiInsertPoint >= 1023)
				{
					continue;
				}
				for(unsigned int i=0; i < u8s.length(); ++i)
				{
					if(uiInsertPoint+i < 1024)
					{
						gsKeyTranslationTable[uiInsertPoint+i] = u8s.at(i);
					}
				}
			}
		}
	}
}

/*************************************************************************************/
/*************************************************************************************/

#include <set>

namespace charSet
{
	static std::map<ECharSet,std::set<wchar_t> > _sets;
};

inline bool testSet(int char_set, charSet::ECharSet es, wchar_t wc)
{
	if(char_set & es)
	{
		std::set<wchar_t>& wcset = charSet::_sets[es];
		return wcset.find(wc) !=  wcset.end();
	}
	return false;
}

bool charSet::isFromSet(char wc, unsigned int char_set)
{
	return charSet::isFromSet((wchar_t)wc, char_set);
}
bool charSet::isFromSet(int wc, unsigned int char_set)
{
	return charSet::IsFromSet((wchar_t)wc, char_set);
}
bool charSet::isFromSet(unsigned int wc, unsigned int char_set)
{
	return charSet::IsFromSet((wchar_t)wc, char_set);
}

bool charSet::isFromSet(wchar_t wc, unsigned int char_set)
{
	bool inSet = false;
	if( inSet |= TestSet(char_set, charSet::CS_SPACE, wc)) return true; 
	if( inSet |= TestSet(char_set, charSet::CS_ALPHA_LC, wc)) return true; 
	if( inSet |= TestSet(char_set, charSet::CS_ALPHA_UC, wc)) return true; 
	if( inSet |= TestSet(char_set, charSet::CS_NUMERIC, wc)) return true; 
	if( inSet |= TestSet(char_set, charSet::CS_SPECIAL_ALPHA_LC, wc)) return true; 
	if( inSet |= TestSet(char_set, charSet::CS_SPECIAL_ALPHA_UC, wc)) return true; 
	if( inSet |= TestSet(char_set, charSet::CS_SPECIAL_NON_CHAR, wc)) return true; 
	return false;
}

void charSet::addToCharSet(ECharSet eset, std::wstring cset)
{
	std::set<wchar_t>& wcset = charSet::_sets[eset];
	for(unsigned int i = 0; i < cset.length(); ++i)
	{
		wcset.insert(cset.at(i));
	}
}

void charSet::initializeCharSets()
{
	charSet::AddToCharSet(charSet::CS_SPACE,			L" ");
	charSet::AddToCharSet(charSet::CS_ALPHA_LC,			L"abcdefghijklmnopqrstuvwxyz");
	charSet::AddToCharSet(charSet::CS_ALPHA_UC,			L"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	charSet::AddToCharSet(charSet::CS_NUMERIC,			L"0123456789");
	charSet::AddToCharSet(charSet::CS_SPECIAL_ALPHA_LC,	L"äöüßáàâéèêóòôúùô");
	charSet::AddToCharSet(charSet::CS_SPECIAL_ALPHA_UC,	L"ÄÖÜÁÀÂÉÈÊÓÒÔÚÙÛ");
	charSet::AddToCharSet(charSet::CS_SPECIAL_NON_CHAR,	L"~*+-_.,:;'´`#°^!\"§$%&/()=?\\{}[]");
}

#endif // USE_CODE_PAGE

/*************************************************************************************/
/*************************************************************************************/
