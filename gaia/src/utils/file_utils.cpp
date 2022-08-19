#include "pch.h"
#include "file_utils.h"

std::string get_extension_from_path(const char* path)
{
	const char* f = strrchr(path, '.');
	return std::string(f + 1);
}

std::string get_name_from_path(const char* path)
{
	const char* bar = strrchr(path, '/');
	const char* f = strrchr(path, '.');
	size_t size = f - bar - 1;
	std::string name(size, 0);
	std::memcpy(name.data(), bar+1, size);
	return name;
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
