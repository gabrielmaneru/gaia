#include "pch.h"
#include "extension.h"

#include <utils/file_utils.h>

inline Extension operator++(Extension& val)
{
    return val = (Extension)(std::underlying_type<Extension>::type(val) + 1);
}

Extension get_extension(const std::string& path)
{
	const std::string cur_ext = get_extension_from_path(path.c_str());
	if (!cur_ext.empty())
	{
		auto ext = Extension::_begin;
		++ext;
		for (; ext < Extension::_end; ++ext)
		{
			std::string ext_name;
			switch (ext)
			{
			default:
				Log_Assert(false, "Incomplete Extension Name");
			case Extension::png:
				ext_name = "png";
				break;
			case Extension::jpg:
				ext_name = "jpg";
				break;
			case Extension::obj:
				ext_name = "obj";
				break;
			case Extension::level:
				ext_name = "level";
				break;
			case Extension::mtl:
				ext_name = "mtl";
				break;
			}

			if (cur_ext == ext_name)
				return ext;
		}
	}
	return Extension::_none;
}
