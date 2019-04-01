#pragma once

#include <string>

#include "PreFile.h"
#include "Folder.h"
#include "FolderOrder.h"
#include "VisitFoldersUtil.h"
#include "StringUtil.h"

using namespace std;
using namespace hfsfolder_model;
using namespace hfsfolder_util;

namespace hfsfolder
{

class ProcessFolders
{
	private:
		static std::string MountBigSize(long double nTam);
		static std::string MountSize(long long nTam);
		static PreFile attributesToPreFile(path sfile);
		static Folder createFolder(path sfile, FolderOrder *folderOrder);
		static bool filterFindFirst(std::vector<Folder> listFolders, const std::string sfolder, Folder *rfolder);
		static std::vector<Folder> process(std::string folder);
		
	public:
		ProcessFolders();
		virtual ~ProcessFolders();
		
		static std::string processFoldersToJson(std::string folder);
		static void processFoldersToFile(std::string data, const std::string sfile);
		static std::string processFoldersToInsert(std::string folder, int naba);
		static std::string processFoldersToCSV(std::string folder);
};

}

