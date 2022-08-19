#pragma once
#include "mesh.h"

#include <resources/resource.h>
#include <utils/obj_loader.h>

class Model : public Resource
{
public:
	Model(const std::string& path, const Extension ext)
		: Resource(path, ext) {}
	Extensions(Extension::obj);
	void draw()const;

protected:
	bool load_internal()override final;
	bool unload_internal()override final;

private:
	std::vector<Mesh*> m_meshes;
};