#include "pch.h"
#include "model.h"

Model::Model(const char* path)
{
	auto result = ObjLoader::load(path);

	Log_Assert(!result.empty(), "Failed to load mesh: {0}", path);

	for each (ObjLoader::Mesh * rawMesh in result)
	{
		u32 vertex_count = (u32)rawMesh->m_vertices.size();
		Mesh* mesh = new Mesh{ vertex_count };
		mesh->m_indices.resize(rawMesh->m_faces.size() * 3);

		std::memcpy(mesh->m_position.data(), rawMesh->m_vertices.data(), vertex_count * sizeof(vec3));

		u32 face_index = 0;
		for each (ObjLoader::Mesh::Face face in rawMesh->m_faces)
		{
			mesh->m_indices[face_index++] = face.m_vertex[0];
			mesh->m_indices[face_index++] = face.m_vertex[1];
			mesh->m_indices[face_index++] = face.m_vertex[2];
		}
		mesh->load();
		m_meshes.push_back(mesh);
	}
}

Model::~Model()
{
	for each (Mesh * mesh in m_meshes)
	{
		delete mesh;
	}
	m_meshes.clear();
}

void Model::draw()
{
	for each (Mesh* mesh in m_meshes)
	{
		mesh->draw();
	}
}
