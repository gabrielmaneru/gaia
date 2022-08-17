#include "pch.h"
#include "file_utils.h"

const char* get_extension_from_path(const char* path)
{
	const char* f = strrchr(path, '.');
	return f + 1;
}

std::string read_file_into_string(const char* path)
{
	std::string output;
	std::ifstream file(path);
	if (!file.is_open())
		return "";
	
	// Get size of file
	file.seekg(0, std::ios::end);
	output.resize(file.tellg());

	// Read file
	file.seekg(0, std::ios::beg);
	file.read(&output[0], output.size());

	file.close();
	return output;
}
