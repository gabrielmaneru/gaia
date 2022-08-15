#include "pch.h"
#include "obj_loader.h"


const ObjLoader::Result ObjLoader::load(const char* filepath)
{
	Result result{};

	// Open file
	std::ifstream file(filepath);
	if (!file.is_open())
	{
		return {};
	}

	// Perform a pre pass over the file initalizing
	// the number of meshes and their sizes
	ObjLoader::initialize_mesh_vectors(result, file);
	
	// Failed to found any mesh
	if (result.empty())
		return {};

	// Reset file handle to start of file
	file.clear();
	file.seekg(0);

	// Perform a second pass over the file
	// setting all the mesh data
	ObjLoader::fill_mesh_data(result, file);

 	return result;
}

void ObjLoader::initialize_mesh_vectors(std::vector<ObjLoader::Mesh*>& meshes, std::ifstream& stream)
{
	u32 cur_vertex_count{ 0u };
	u32 cur_uv_count{ 0u };
	u32 cur_normal_count{ 0u };
	u32 cur_face_count{ 0u };

	auto store_last_object_sizes = [&]()
	{
		// Store last object
		if (cur_face_count != 0u)
		{
			// Push unknown mesh if name wasn't found
			if (meshes.empty())
			{
				meshes.push_back(new Mesh{});
				meshes.back()->m_name = "<unknown>";
			}

			// Resize mesh
			Mesh* mesh = meshes.back();
			mesh->m_vertices.resize(cur_vertex_count);
			mesh->m_uv_coordinates.resize(cur_uv_count);
			mesh->m_normals.resize(cur_normal_count);
			mesh->m_faces.resize(cur_face_count);
		}

		// Reset counters
		cur_vertex_count = 0u;
		cur_uv_count = 0u;
		cur_normal_count = 0u;
		cur_face_count = 0u;
	};

	// Iterate over the file to find out about meshes and the item count
	std::string line;
	while (std::getline(stream, line))
	{
		// Empty line
		if (line.size() == 0u)
			continue;

		// Comment
		if (line[0] == '#')
			continue;

		// Object
		if (line.rfind("o ") == 0)
		{
			// Store previous object
			store_last_object_sizes();

			// Start mesh wih name
			meshes.push_back(new Mesh{});
			meshes.back()->m_name = line.substr(2u); // skip "o "
		}

		// Vertex
		else if (line.rfind("v ") == 0)
			++cur_vertex_count;

		// UV coordinates
		else if (line.rfind("vt ") == 0)
			++cur_uv_count;

		// Normal
		else if (line.rfind("vn ") == 0)
			++cur_normal_count;

		// Face
		else if (line.rfind("f ") == 0)
			++cur_face_count;
	}

	// Push last object info
	store_last_object_sizes();
}

void ObjLoader::fill_mesh_data(std::vector<ObjLoader::Mesh*>& meshes, std::ifstream& stream)
{
	bool is_first_object{ true };
	u32 cur_mesh_idx{ 0u };
	u32 cur_vertex_idx{ 0u };
	u32 cur_uv_idx{ 0u };
	u32 cur_normal_idx{ 0u };
	u32 cur_face_idx{ 0u };

	// Iterate over the file to fill the mesh information
	std::string line;
	while (std::getline(stream, line))
	{
		// Empty line
		if (line.size() == 0u)
			continue;

		// Comment
		if (line[0] == '#')
			continue;

		// Object
		if (line.rfind("o ") == 0)
		{
			if (is_first_object)
				is_first_object = false;
			else
				++cur_mesh_idx;

			// Reset counters
			cur_vertex_idx = 0u;
			cur_uv_idx = 0u;
			cur_normal_idx = 0u;
			cur_face_idx = 0u;
		}

		// Vertex
		else if (line.rfind("v ") == 0)
		{
			parse_vec3(line, meshes[cur_mesh_idx]->m_vertices[cur_vertex_idx++]);
		}

		// UV coordinates
		else if (line.rfind("vt ") == 0)
		{
			parse_vec2(line, meshes[cur_mesh_idx]->m_uv_coordinates[cur_uv_idx++]);
		}

		// Normal
		else if (line.rfind("vn ") == 0)
		{
			parse_vec3(line, meshes[cur_mesh_idx]->m_normals[cur_normal_idx++]);
		}

		// Face
		else if (line.rfind("f ") == 0)
		{
			parse_face(line, meshes[cur_mesh_idx]->m_faces[cur_face_idx++]);
		}
	}
}

void ObjLoader::parse_vec3(const std::string& line, vec3& out)
{
	//Compute starts
	size_t s1 = line.find(' ') + 1;
	size_t s2 = line.find(' ', s1) + 1;
	size_t s3 = line.find(' ', s2) + 1;

	// X
	out[0] = static_cast<float>(std::atof(line.substr(s1, s2 - s1 - 1).c_str()));

	// Y
	out[1] = static_cast<float>(std::atof(line.substr(s2, s3 - s2 - 1).c_str()));

	// Z
	out[2] = static_cast<float>(std::atof(line.substr(s3).c_str()));
}

void ObjLoader::parse_vec2(const std::string& line, vec2& out)
{
	//Compute starts
	size_t s1 = line.find(' ') + 1;
	size_t s2 = line.find(' ', s1) + 1;

	// X
	out[0] = static_cast<float>(std::atof(line.substr(s1, s2 - s1 - 1).c_str()));

	// Y
	out[1] = static_cast<float>(std::atof(line.substr(s2).c_str()));
}

void ObjLoader::parse_face(const std::string& line, ObjLoader::Mesh::Face& out)
{
	//Compute starts
	size_t s1 = line.find(' ') + 1;
	size_t s2 = line.find(' ', s1) + 1;
	size_t s3 = line.find(' ', s2) + 1;
	//Compute the six barriers
	size_t b11 = line.find('/', s1) + 1;
	size_t b12 = line.find('/', b11) + 1;
	size_t b21 = line.find('/', s2) + 1;
	size_t b22 = line.find('/', b21) + 1;
	size_t b31 = line.find('/', s3) + 1;
	size_t b32 = line.find('/', b31) + 1;

	out.m_vertex[0] = static_cast<u32>(std::atoi(line.substr(s1, b11 - s1 - 1).c_str()));
	out.m_vertex[1] = static_cast<u32>(std::atoi(line.substr(s2, b21 - s2 - 1).c_str()));
	out.m_vertex[2] = static_cast<u32>(std::atoi(line.substr(s3, b31 - s3 - 1).c_str()));

	if (b12 - b11 > 1)
	{
		out.m_uv[0] = static_cast<u32>(std::atoi(line.substr(b11, b12 - b11 - 1).c_str()));
	}
	if (b22 - b21 > 1)
	{
		out.m_uv[1] = static_cast<u32>(std::atoi(line.substr(b21, b22 - b21 - 1).c_str()));
	}
	if (b32 - b31 > 1)
	{
		out.m_uv[2] = static_cast<u32>(std::atoi(line.substr(b31, b32 - b31 - 1).c_str()));
	}

	if (s2 - b12 > 1)
	{
		out.m_normal[0] = static_cast<u32>(std::atoi(line.substr(b12, s2 - b12 - 1).c_str()));
	}
	if (s3 - b22 > 1)
	{
		out.m_normal[1] = static_cast<u32>(std::atoi(line.substr(b22, s3 - b22 - 1).c_str()));
	}
	if (line.size() - b32 > 0)
	{
		out.m_normal[2] = static_cast<u32>(std::atoi(line.substr(b32, line.size() - b32).c_str()));
	}
}