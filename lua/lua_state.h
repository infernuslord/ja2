#ifndef _LUA_STATE_H_
#define _LUA_STATE_H_

#include <Lua Interpreter.h>

namespace lua
{
	enum State
	{
		LUA_STATE,
		LUA_STATE_STRUCTURE,
		LUA_STATE_GUI,
	};
};

class LuaState
{
	class Registry
	{
	public:
		void CreateCallbackTable();
		void GetCallbackTable();

		void SetCallback(const char* callback_name);
		void GetCallback(const char* callback_name);

		void CreateUserDataTable();
		void GetUserDataTable();
	private:
		friend class LuaState;
		Registry(lua_State* L);
		lua_State* _L;
	};
public:
	LuaState(lua_State* state, bool own=false);
	LuaState();
	~LuaState();

	static void			INIT(lua::State state_id);
	static void			CLOSE(lua::State state_id);
	static LuaState		GET(lua::State state_id);

	inline lua_State* operator()() { return _L; }

	inline Registry& registry() { return _registry; }

	bool EvalFile(const char* filename);

	bool EvalString(const char* lua_str, size_t length, const char* id_str);
	bool EvalString(const wchar_t* lua_str, size_t length, const char* id_str);

	bool CallFunction(const char* function_name);
private:
	void init();
	void close();
private:
	lua_State*		_L;
	bool			_own;
	Registry		_registry;
};




#endif // _LUA_STATE_H_
