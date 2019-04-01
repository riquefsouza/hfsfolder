#include "VisitFoldersUtil.h"

namespace hfsfolder_util
{

	VisitFoldersUtil::VisitFoldersUtil()
	{
	}

	VisitFoldersUtil::~VisitFoldersUtil()
	{
	}

	std::vector<path> VisitFoldersUtil::getPathsFromFiles(std::string folder)
	{
		std::vector<path> lista;

		path current_dir(folder);
		
		lista.push_back(folder);

		for (recursive_directory_iterator iter(current_dir), end;
			iter != end;
			++iter)
		{
			lista.push_back(iter->path());
		}
		return lista;
	}

	std::vector<path> VisitFoldersUtil::getPathsFromFiles(std::string folder, std::string spattern)
	{
		std::vector<path> lista;

		path current_dir(folder);
		
		lista.push_back(folder);

		boost::regex pattern(spattern);
		for (recursive_directory_iterator iter(current_dir), end;
			iter != end;
			++iter)
		{
			std::string name = iter->path().leaf().string();
			if (regex_match(name, pattern)) {
				lista.push_back(iter->path());
			}
		}
		return lista;
	}

}
