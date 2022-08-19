#pragma once
#include "extension.h"
#include <graphics/model.h>

template<typename T>
using ResourceMap = std::map<std::string, shared<T>>;

template<typename ... Args>
using TupleMap = std::tuple<ResourceMap<Args>...>;

using ResourceMaps = TupleMap<
	Model
>;

class ResourceManager
{
public:
	static void initialize();
	static void clear();

	template<typename T>
	static shared<T> get(const std::string& name);
	template<typename T>
	static ResourceMap<T>& get_map();

private:
	static ResourceManager instance;
	void add_resource(const std::string& path, const Extension);
	ResourceMaps m_resources;
};

template<typename T>
inline shared<T> ResourceManager::get(const std::string& name)
{
	ResourceMap<T>& resource_map = get_map<T>();
	auto key = resource_map.find(name);
	if (key == resource_map.end())
		return nullptr;

	if (!key->second->is_loaded())
		key->second->load_resource();
	return shared<T>{key->second};
}

template<typename T>
inline ResourceMap<T>& ResourceManager::get_map()
{
	return std::get<ResourceMap<T>>(instance.m_resources);
}