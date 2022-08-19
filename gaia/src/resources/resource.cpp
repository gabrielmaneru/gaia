#include "pch.h"
#include "resource.h"

void Resource::load_resource()
{
	if (!m_loaded)
	{
		m_loaded = load_internal();
		if(!m_loaded)
			Log_Error("Couldn't load {0} at {1}", get_name(), m_path);
	}
	else
		Log_Warn("Loading twice {0} at {1}", get_name(), m_path);
}

void Resource::unload_resource()
{
	if (m_loaded)
	{
		m_loaded = !unload_internal();
		if (m_loaded)
			Log_Error("Couldn't unload {0} at {1}", get_name(), m_path);
	}
	else
		Log_Warn("Unloading twice {0} at {1}", get_name(), m_path);
}

Resource::Resource(const std::string& path, const Extension ext)
	: m_loaded(false)
	, m_path(path)
	, m_extension(ext)
{
}
