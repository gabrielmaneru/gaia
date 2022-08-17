#pragma once

constexpr int mesh_buffer_count = 4;
class Mesh
{
public:
	Mesh(u32 vertex_count);
	~Mesh();
	void load();
	void draw();

	std::vector<u32> m_indices;
	std::vector<vec3> m_position;
	std::vector<vec3> m_normal;
	std::vector<vec2> m_uv_coord;

private:
	u32 m_vertex_count;
	u32 m_vertex_array_id;
	std::array<u32, mesh_buffer_count> m_vertex_buffer_ids;
};