#pragma once
#include <map>
#include <vector>
#include <memory>

#include <debug/logger.h>

using u8 = unsigned char;
using u32 = unsigned int;
struct urect {
	u32 x, y;
	bool operator==(const urect& r)const {
		return x == r.x && y == r.y;
	}
};