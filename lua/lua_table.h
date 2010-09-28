#ifndef _LUA_TABLE_H_
#define _LUA_TABLE_H_

#include "lua/lua_state.h"

class LuaTable
{
public:
	LuaTable(LuaState L) : _L(L)
	{
		lua_newtable(_L());
		_off = -1;
	}
	LuaTable(LuaState L, int st_off) : _L(L), _off(st_off) {};
	bool is_valid() {
		if(lua_istable(_L(), _off))
		{
			return true;
		}
		return false;
	}

	template<typename T>
	bool getValue(const char* index, T& value);

	template<typename T>
	T* getValue(const char* index)
	{
		if(is_valid())
		{
			lua_getfield(_L(), _off, index);
			T* value = LuaInterface::luaGetTypedUserData<T>(_L, -1);
			return value;
		}
		return NULL;
	}

	template<typename T>
	bool setValue(const char* index, T const& value);

	template<typename T>
	bool setValue(int index, T const& value);

private:
	LuaState	_L;
	int			_off;
};

/////////////////////
template<> bool LuaTable::getValue<std::string>(const char* index, std::string& value);
template<> bool LuaTable::getValue<double>(const char* index, double& value);
template<> bool LuaTable::getValue<int>(const char* index, int& value);
template<> bool LuaTable::getValue<unsigned int>(const char* index, unsigned int& value);
template<> bool LuaTable::getValue<bool>(const char* index, bool& value);

/////////////////////
template<> bool LuaTable::setValue<std::string>(const char* index, std::string const& value);
template<> bool LuaTable::setValue<double>(const char* index, double const& value);
template<> bool LuaTable::setValue<int>(const char* index, int const& value);
template<> bool LuaTable::setValue<unsigned int>(const char* index, unsigned int const& value);
template<> bool LuaTable::setValue<bool>(const char* index, bool const& value);

template<> bool LuaTable::setValue<std::string>(int index, std::string const& value);
template<> bool LuaTable::setValue<double>(int index, double const& value);
template<> bool LuaTable::setValue<int>(int index, int const& value);
template<> bool LuaTable::setValue<unsigned int>(int index, unsigned int const& value);
template<> bool LuaTable::setValue<bool>(int index, bool const& value);

#endif // _LUA_TABLE_H_
