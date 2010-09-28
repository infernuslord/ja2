#include "lua/lua_table.h"

template<>
bool LuaTable::getValue<std::string>(const char* index, std::string& value)
{
	if(is_valid())
	{
		lua_State* L = _L();
		lua_getfield(L, _off, index);
		if(lua_isstring(L, -1))
		{
			value = lua_tostring(L,-1);
		}
		lua_pop(L,1);
		return true;
	}
	return false;
}

template<>
bool LuaTable::getValue<double>(const char* index, double& value)
{
	if(is_valid())
	{
		lua_State* L = _L();
		lua_getfield(L, _off, index);
		if(lua_isnumber(L, -1))
		{
			value = lua_tonumber(L,-1);
			lua_pop(L,1);
			return true;
		}
		lua_pop(L,1);
	}
	return false;
}

template<>
bool LuaTable::getValue<int>(const char* index, int& value)
{
	double tmp;
	bool b = getValue<double>(index,tmp);
	value = (int)tmp;
	return b;
}
template<>
bool LuaTable::getValue<unsigned int>(const char* index, unsigned int& value)
{
	double tmp;
	bool b = getValue<double>(index,tmp);
	value = (unsigned int)tmp;
	return b;
}

template<>
bool LuaTable::getValue<bool>(const char* index, bool& value)
{
	if(is_valid())
	{
		lua_State* L = _L();
		lua_getfield(L, _off, index);
		if(lua_isboolean(L, -1))
		{
			value = lua_toboolean(L,-1) != 0;
			lua_pop(L,1);
			return true;
		}
		lua_pop(L,1);
	}
	return false;
}

/////////////////////////////////

template<>
bool LuaTable::setValue<std::string>(const char* index, std::string const& value)
{
	if(is_valid())
	{
		lua_State* L = _L();
		
		lua_pushstring(L, index);
		lua_pushstring(L, value.c_str());
		lua_rawset(L, -3);
		return true;
	}
	return false;
}

template<>
bool LuaTable::setValue<double>(const char* index, double const& value)
{
	if(is_valid())
	{
		lua_State* L = _L();
		
		lua_pushstring(L, index);
		lua_pushnumber(L, value);
		lua_rawset(L, -3);
		return true;
	}
	return false;
}

template<>
bool LuaTable::setValue<int>(const char* index, int const& value)
{
	return setValue<double>(index, (double)value);
}
template<>
bool LuaTable::setValue<unsigned int>(const char* index, unsigned int const& value)
{
	return setValue<double>(index, (double)value);
}

template<>
bool LuaTable::setValue<bool>(const char* index, bool const& value)
{
	if(is_valid())
	{
		lua_State* L = _L();
		
		lua_pushstring(L, index);
		lua_pushboolean(L, value);
		lua_rawset(L, -3);
		return true;
	}
	return false;
}

/////////////////////////////////////

template<> 
bool LuaTable::setValue<std::string>(int index, std::string const& value)
{
	if(is_valid())
	{
		lua_State* L = _L();
		
		lua_pushinteger(L, index);
		lua_pushstring(L, value.c_str());
		lua_rawset(L, -3);
		return true;
	}
	return false;
}

template<>
bool LuaTable::setValue<double>(int index, double const& value)
{
	if(is_valid())
	{
		lua_State* L = _L();
		
		lua_pushinteger(L, index);
		lua_pushnumber(L, value);
		lua_rawset(L, -3);
		return true;
	}
	return false;
}

template<>
bool LuaTable::setValue<int>(int index, int const& value)
{
	return setValue<double>(index, (double)value);
}
template<>
bool LuaTable::setValue<unsigned int>(int index, unsigned int const& value)
{
	return setValue<double>(index, (double)value);
}

template<>
bool LuaTable::setValue<bool>(int index, bool const& value)
{
	if(is_valid())
	{
		lua_State* L = _L();
		
		lua_pushinteger(L, index);
		lua_pushboolean(L, value);
		lua_rawset(L, -3);
		return true;
	}
	return false;
}
