#pragma once
#include <map>
#include <vector>
#include <memory>

#include <debug/logger.h>

#define GLM_FORCE_XYZW_ONLY
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

using u8 = unsigned char;
using u32 = unsigned int;
struct urect {
	u32 x, y;
	bool operator==(const urect& r)const {
		return x == r.x && y == r.y;
	}
};

using vec2 = glm::vec2;
using vec3 = glm::vec3;
using vec4 = glm::vec4;
using ivec2 = glm::ivec2;
using ivec3 = glm::ivec3;
using ivec4 = glm::ivec4;
using mat3 = glm::mat3;
using mat4 = glm::mat4;
using quat = glm::quat;