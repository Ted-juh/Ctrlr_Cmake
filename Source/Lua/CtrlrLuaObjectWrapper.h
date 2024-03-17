#pragma once
#include "luabind/object_fwd.hpp"

class CtrlrLuaObjectWrapper
{
	public:
		CtrlrLuaObjectWrapper();
    CtrlrLuaObjectWrapper(luabind::object const& other);
		operator luabind::object &();
		operator luabind::object();
		const luabind::object &getLuabindObject() const;
		const luabind::object &getObject() const;

	private:
		luabind::object *o;
};