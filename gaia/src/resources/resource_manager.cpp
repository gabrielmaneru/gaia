#include "pch.h"
#include "resource_manager.h"


#include <utils/tuple.h>
ResourceManager ResourceManager::instance = {};

void ResourceManager::initialize()
{
	_WIN32_FIND_DATAA file;
	std::vector<std::string> folders;
	HANDLE handle;
	folders.push_back("content");

	// search in the folder
	for (int i = 0; i < folders.size(); i++)
	{
		handle = FindFirstFileA((LPCSTR)(folders[i] + "/*").c_str(), &file);
		if (!handle)
			continue;
		do
		{
			if (file.cFileName[0] == '.')
				continue;

			if (FILE_ATTRIBUTE_DIRECTORY & file.dwFileAttributes)
			{
				folders.push_back(folders[i] + '/' + (char*)file.cFileName);
				continue;
			}
			auto ext = strrchr((char*)file.cFileName, '.');

			if (ext != nullptr)
			{
				std::string pathname = folders[i] + '/' + file.cFileName;
				Extension extension = get_extension(pathname);
				if (extension != Extension::_none)
					instance.add_resource(pathname, extension);
			}

		} while (FindNextFileA(handle, &file));
		FindClose(handle);
	}
}

void ResourceManager::clear()
{
	tuple_for_each(instance.m_resources, [](auto& map) {
		for (auto& res : map) {
			if (res.second->is_loaded())
				res.second->unload_resource();
		}
		});
}

#define MapElementType std::decay<decltype(map)>::type::mapped_type::element_type
void ResourceManager::add_resource(const std::string& path, const Extension ext)
{
	std::string name = get_name_from_path(path.c_str());
	tuple_for_each(m_resources, [&path, &ext, &name](auto& map) {
		if (map.find(name) == map.end())
		{
			for (auto& stored_ext : MapElementType::m_extensions) {
				if (stored_ext == ext)
				{
					map[name] = std::make_shared<MapElementType>(path.c_str(), ext);
					break;
				}
			}
		}
		});
}
#undef MapElementType
