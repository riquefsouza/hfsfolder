#pragma once

#include <string>

#include "PreFile.h"
#include "Folder.h"
#include "FolderOrder.h"
//JSONListConverter;
#include "VisitFoldersUtil.h"

using namespace std;
using namespace hfsfolder_model;
using namespace hfsfolder_util;

namespace hfsfolder
{

class ProcessFolders
{
	private:
		std::string LongLongToStr(const long long valor);
		std::string LongDoubleToStr(const long double valor);
		std::string MontaTamanhoBig(long double nTam);
		std::string MontaTamanho(long long nTam);
		PreFile attributesToPreFile(path sfile);
		std::string replaceAll(const std::string texto, 
			const std::string velho, const std::string novo);
		bool startsWith(const std::string texto, const std::string subtexto);
		int pos(const std::string subtexto, const std::string texto);
		bool contains(const std::string texto, const std::string subtexto);
		int lastIndexOf(const std::string texto, const char subtexto);
		Folder createFolder(path sfile, FolderOrder *folderOrder);
		bool filterFindFirst(std::vector<Folder> listFolders, const std::string sfolder, Folder *rfolder);
		std::vector<Folder> process(std::string folder);
		
	public:
		ProcessFolders();
		virtual ~ProcessFolders();
		
		std::string processFoldersToJson(std::string folder);
		void processFoldersToFile(std::string data, std::string file);
		std::string processFoldersToInsert(std::string folder, int naba);
		std::string processFoldersToCSV(std::string folder);
};

}

