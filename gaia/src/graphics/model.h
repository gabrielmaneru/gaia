#pragma once
#include "mesh.h"

#include <utils/obj_loader.h>

class Model
{
public:
	Model(const char* path);
	~Model();
	void draw();

private:

	std::vector<Mesh*> m_meshes;
};