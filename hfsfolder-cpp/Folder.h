#pragma once
#include <string>
#include "PreFile.h"

using namespace std;

namespace hfsfolder_model
{

class Folder : public PreFile
{
	private:
		int code;
		int order;
		int parentCodFolder;
		char folderType;
		std::string path;
		std::string parentName;
		std::string parentPath;
		
	public:
		Folder();
		Folder(PreFile *preFile);
		virtual ~Folder();

		int getCode();
		void setCode(int code);
		int getOrder();
		void setOrder(int order);
		int getParentCodFolder();
		void setParentCodFolder(int parentCodFolder);
		char getFolderType();
		void setFolderType(char folderType);
		std::string getPath();
		void setPath(std::string path);
		std::string getParentName();
		void setParentName(std::string parentName);
		std::string getParentPath();
		void setParentPath(std::string parentPath);
		void limparDados();
		std::string toString();
		std::string toInsert(int naba);
		std::string toCVS();
};

}

