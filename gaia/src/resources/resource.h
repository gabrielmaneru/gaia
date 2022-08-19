#pragma once
#include "extension.h"
#include <utils/file_utils.h>

class Resource
{
public:
	virtual ~Resource()=default;
	void load_resource();
	void unload_resource();
	bool is_loaded()const { return m_loaded; }
	std::string get_name()const { return get_name_from_path(m_path.c_str()); }
	std::string get_extension()const { return get_extension_from_path(m_path.c_str()); }

protected:
	Resource(const std::string& path, const Extension ext);
	virtual bool load_internal() = 0;
	virtual bool unload_internal() = 0;
	std::string m_path;

private:
	Resource() = delete;
	bool m_loaded;
	Extension m_extension;
};