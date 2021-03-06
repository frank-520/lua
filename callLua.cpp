// callLua.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

extern "C" {
#include "tmp/lua.hpp"
#include "tmp/lauxlib.h"
#include "tmp/lualib.h"
}

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include <iostream>
#pragma comment(lib,"tmp/lua51.lib")

#include "People.h"

using namespace std;


/*
-- First.lua
local First = {}

function First.add(x, y)
	return x + y;
end

function getName()
	return "hahaha";
end

return First

*/


/*
-- Call.lua
g_First = require "First"

Call = {}

function Call.call_getAdd(x,y)
	return g_First.add(x,y)
end

return Call

*/

//调用lua中的add函数
int call_lua_add(lua_State *L)
{
	lua_getglobal(L, "add"); //获取add函数
	lua_pushnumber(L, 123); //第一个操作数入栈
	lua_pushnumber(L, 456); //第二个操作数入栈
	lua_pcall(L, 2, 1, 0); //调用函数，2个参数，1个返回值
	int sum = (int)lua_tonumber(L, -1); //获取栈顶元素（结果）
	lua_pop(L, 1); //栈顶元素出栈
	return sum;
}

string call_lua_getName(lua_State *L)
{
	lua_getglobal(L, "getName"); //获取add函数
	lua_pcall(L, 0, 1, 0); //调用函数，0个参数，1个返回值
	string name = (char*)lua_tolstring(L, -1,NULL); //获取栈顶元素（结果）
	lua_pop(L, 1); //栈顶元素出栈
	return name;
}

int call_lua_objAdd(lua_State *L)
{
	//将First这个变量放在栈顶，对应lua文件中的First这个table
	//lua_getglobal(L, "First");

	lua_getglobal(L, "Call");

	//如果First不是一个table，返回错误
	if (!lua_istable(L, -1))
	{
		printf("Call is not table\n");
		exit(0);
	}

	lua_pushstring(L,"call_getAdd");
	lua_gettable(L,-2);
	if (!lua_isfunction(L,-1))
	{
		printf("call_getAdd is not function\n");
		exit(0);
	}

	lua_pushnumber(L,111);
	lua_pushnumber(L,222);

	lua_pcall(L, 2, 1, 0); //调用函数，2个参数，1个返回值
	int result = (int)lua_tonumber(L, -1); //获取栈顶元素（结果）
	lua_pop(L, 1); //栈顶元素出栈
	return result;
}

int main()
{
	lua_State *L = luaL_newstate(); //新建lua解释器
	luaL_openlibs(L); //载入lua所有函数库
	//luaL_dofile(L, "First.lua"); //执行"First.lua"文件中的代码

	luaL_dofile(L, "Call.lua"); //执行"First.lua"文件中的代码
	//printf("%s\n", call_lua_getName(L).c_str());
	printf("%d\n", call_lua_objAdd(L));
	
	lua_close(L); //释放内存

	const char* test = "hello,world";
	printf("%s\n", test);
	test = "123";
	printf("%s\n", test);

	char test1[] = "hello,frank";
	printf("%s\n", test1);
	test1[0] = 'a';
	printf("%s\n", test1);

	return 0;
}

