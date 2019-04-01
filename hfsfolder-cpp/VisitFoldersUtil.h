#pragma once

#include "boost/filesystem.hpp"
#include "boost/regex.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace boost::filesystem;
using namespace std;

namespace hfsfolder_util
{

	class VisitFoldersUtil
	{
	public:
		VisitFoldersUtil();
		virtual ~VisitFoldersUtil();
		static std::vector<path> getPathsFromFiles(std::string folder);
		static std::vector<path> getPathsFromFiles(std::string folder, std::string spattern);
	};

}

