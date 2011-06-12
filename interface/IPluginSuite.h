#ifndef _IPLUGINSUITE_H_
#define _IPLUGINSUITE_H_

#include "IPlugin.h"
#include "common/Singleton.h"
#include "Interface/PluginManager.h"

#define DECLARE_PLUGIN(name) \
class name { \
public: \
	name(); \
}; \

#define PLUGIN_BEGIN(name) \
	name _##name##_plugin; \
	name::name() { \

#define PLUGIN_ADD(p) \
	Interface::PluginManager::GetSingleton().Load(Interface::IPlugin::Pointer(new p)); \

#define PLUGIN_END() \
	} \

#endif // _IPLUGINSUITE_H_
