#include "pch.h"
#include "mesh.h"

#include <glad/glad.h>

Mesh::Mesh(u32 vertex_count)
	: m_vertex_count(vertex_count)
{
	m_position.resize(m_vertex_count, vec3{ 0.0f });
	m_normal.resize(m_vertex_count, vec3{ 0.0f });
	m_uv_coord.resize(m_vertex_count, vec2{ 0.0f });

	// Create VAO
	glGenVertexArrays(1, &m_vertex_array_id);
	glBindVertexArray(m_vertex_array_id);
	// Create VBO
	glGenBuffers(mesh_buffer_count, m_vertex_buffer_ids.data());

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glBindVertexArray(m_vertex_array_id);
	// Destroy VBO
	glDeleteBuffers(mesh_buffer_count, m_vertex_buffer_ids.data());
	// Destoy VAO
	glDeleteVertexArrays(1, &m_vertex_array_id);

	glBindVertexArray(0);
}

void Mesh::load()
{
	glBindVertexArray(m_vertex_array_id);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertex_buffer_ids[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(u32), m_indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ids[1]);
	glBufferData(GL_ARRAY_BUFFER, m_vertex_count * sizeof(vec3), m_position.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ids[2]);
	glBufferData(GL_ARRAY_BUFFER, m_vertex_count * sizeof(vec3), m_normal.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ids[3]);
	glBufferData(GL_ARRAY_BUFFER, m_vertex_count * sizeof(vec2), m_uv_coord.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindVertexArray(0);
}

void Mesh::draw()
{
	glBindVertexArray(m_vertex_array_id);
	glDrawElements(GL_TRIANGLES, (int)m_indices.size(), GL_UNSIGNED_INT, nullptr);

	glBindVertexArray(0);
}
