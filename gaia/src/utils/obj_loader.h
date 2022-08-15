#pragma once
#include <fstream>

class ObjLoader
{
public:

	struct Mesh
	{
		struct Face
		{
			u32 m_vertex[3];
			u32 m_uv[3];
			u32 m_normal[3];
		};

		std::string m_name;
		std::vector<vec3> m_vertices;
		std::vector<vec2> m_uv_coordinates;
		std::vector<vec3> m_normals;
		std::vector<Face> m_faces;
	};

	using Result = std::vector<Mesh*>;
	static const Result load(const char* filepath);

private:
	static void initialize_mesh_vectors(std::vector<Mesh*>& meshes, std::ifstream& stream);
	static void fill_mesh_data(std::vector<Mesh*>& meshes, std::ifstream& stream);

	static void parse_vec3(const std::string& line, vec3& out);
	static void parse_vec2(const std::string& line, vec2& out);
	static void parse_face(const std::string& line, Mesh::Face& out);
};