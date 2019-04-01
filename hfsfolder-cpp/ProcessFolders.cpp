#include "ProcessFolders.h"

#include <cstdlib>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <set>
#include <fstream>
#include <boost/algorithm/string.hpp>

#if !defined (S_IWUSR)
#define S_IWUSR 00200         /* write permission: owner. */
#endif /* !S_IWUSR */

using namespace std;
using namespace boost::algorithm;
using namespace hfsfolder_model;
using namespace hfsfolder_util;

namespace hfsfolder
{

	ProcessFolders::ProcessFolders()
	{
	}

	ProcessFolders::~ProcessFolders()
	{
	}

	std::string ProcessFolders::MountBigSize(long double nTam) {
		long long nUmKilo, nUmMega, nUmGiga, nUmTera, nUmPeta;

		nUmKilo = 1024;
		nUmMega = nUmKilo * nUmKilo;
		nUmGiga = nUmMega * nUmKilo;
		nUmTera = nUmGiga * nUmKilo;
		nUmPeta = nUmTera * nUmKilo;

		if (nTam < nUmKilo) {
			return StringUtil::LongDoubleToStr(nTam) + " Byte(s)";
		}
		else if (nTam > nUmKilo && nTam < nUmMega) {
			nTam = nTam / nUmKilo;
			return StringUtil::LongDoubleToStr(nTam) + " KByte(s)";
		}
		else if (nTam > nUmMega && nTam < nUmGiga) {
			nTam = nTam / nUmMega;
			return StringUtil::LongDoubleToStr(nTam) + " MByte(s)";
		}
		else if (nTam > nUmGiga && nTam < nUmTera) {
			nTam = nTam / nUmGiga;
			return StringUtil::LongDoubleToStr(nTam) + " GByte(s)";
		}
		else if (nTam > nUmTera && nTam < nUmPeta) {
			nTam = nTam / nUmTera;
			return StringUtil::LongDoubleToStr(nTam) + " TByte(s)";
		}
		else {
			nTam = nTam / nUmPeta;
			return StringUtil::LongDoubleToStr(nTam) + " PByte(s)";
		}
	}

	std::string ProcessFolders::MountSize(long long nTam) {
		if (nTam > 0) {
			return MountBigSize((long double)nTam);
		}
		else {
			return "";
		}
	}

	PreFile ProcessFolders::attributesToPreFile(path sfile) {
		struct stat fileInfo;
		ptime datahora;
		std::string sAtributos = "";
		PreFile preFile;

		std::string sName = sfile.leaf().string();
		sName = replace_all_copy(sName, "'", "''");
		preFile.setName(sName);
		preFile.setOriginalPath(sfile.string());

		if (_access(preFile.getOriginalPath().c_str(), 0) == 0) {
			stat(preFile.getOriginalPath().c_str(), &fileInfo);

			datahora = from_time_t(fileInfo.st_mtime);

			if ((fileInfo.st_mode & S_IFMT) == S_IFDIR) {
				sAtributos += "[DIR]";
				preFile.setDirectory(true);
			}
			else {
				sAtributos += "[ARQ]";
				preFile.setDirectory(false);
			}

			//S_IREAD S_IWRITE
			if ((fileInfo.st_mode & S_IFMT) != S_IWUSR) {
				sAtributos += "[ROL]";
			}

			preFile.setSize(fileInfo.st_size);
			preFile.setModified(datahora);
			preFile.setAttributes(sAtributos);
		}
		else {
			preFile.setSize(0);
			preFile.setModified(second_clock::local_time());
			preFile.setAttributes("");
		}

		preFile.setFormatedSize(MountSize(preFile.getSize()));
		//preFile.setFormatedModified(to_iso_extended_string(preFile.getModified()));
		preFile.setFormatedModified(StringUtil::FormatDateTime(to_tm(preFile.getModified())));

		return preFile;
	}

	Folder ProcessFolders::createFolder(path sfile, FolderOrder *folderOrder) {
		PreFile preFile = attributesToPreFile(sfile);
		Folder dir(preFile);

		if (preFile.isDirectory()) {
			dir.setFolderType('D');
		}
		else {
			dir.setFolderType('A');
		}

		std::string sPath = preFile.getOriginalPath();

		boost::regex expr{ "[a-zA-Z]:\\\\" };
		boost::smatch what;
		if (boost::regex_search(sPath, what, expr)) {
			if (what.length() > 0) {
				sPath = sPath.substr(3);
				dir.separatorChar = '\\';
			}
		}

		boost::regex expr2{ "[a-zA-Z]:/" };
		boost::smatch what2;
		if (boost::regex_search(sPath, what2, expr2)) {
			if (what2.length() > 0) {
				sPath = sPath.substr(3);
				dir.separatorChar = '/';
			}
		}
		
		if (starts_with(sPath, "/")) {
			sPath = sPath.substr(1);
			dir.separatorChar = '/';
		}

		sPath = replace_all_copy(sPath, "'", "''");
		std::replace(sPath.begin(), sPath.end(), '\\', '/');

		dir.setPath(sPath);
		dir.setOriginalPath(preFile.getOriginalPath());

		if (!contains(dir.getPath(), "/")) {
			folderOrder->setCodFolder(folderOrder->getCodFolder() + 1);
			folderOrder->setOrder(1);
		}
		else {
			folderOrder->setOrder(folderOrder->getOrder() + 1);
		}

		dir.setCode(folderOrder->getCodFolder());
		dir.setOrder(folderOrder->getOrder());

		return dir;
	}

	bool ProcessFolders::filterFindFirst(std::vector<Folder> listFolders, const std::string sfolder, Folder *rfolder) {

		for (unsigned int i = 0; i < listFolders.size(); i++) {
			Folder folder = listFolders.at(i);

			if (sfolder == folder.getOriginalPath()) {
				rfolder->clone(folder);
				return true;
			}
		}

		return false;
	}

	std::vector<Folder> ProcessFolders::process(std::string folder) {
		std::vector<Folder> listFolders;
		Folder dir;
		FolderOrder* folderOrder = new FolderOrder(-1, 0);

		std::cout << "Processing folders!" << std::endl;

		std::vector<path> listaPaths = VisitFoldersUtil::getPathsFromFiles(folder);

		for (unsigned int i = 0; i < listaPaths.size(); i++) {
			path spath = listaPaths.at(i);

			dir = createFolder(spath, folderOrder);
			listFolders.push_back(dir);
		}

		for (unsigned int i = 0; i < listFolders.size(); i++) {
			Folder item = listFolders.at(i);

			int nlast = StringUtil::lastIndexOf(item.getOriginalPath(), item.separatorChar);
			std::string pathChild = item.getOriginalPath().substr(0, nlast);

			Folder* pathFather = new Folder();

			if (filterFindFirst(listFolders, pathChild, pathFather)) {
				item.setParentCodFolder(pathFather->getOrder());
				item.setParentName(pathFather->getName());
				item.setParentPath(pathFather->getPath());
				
				listFolders.at(i) = item;
			}
		}

		std::sort(listFolders.begin(), listFolders.end(), Folder::compareTo);

		return listFolders;
	}

	std::string ProcessFolders::processFoldersToJson(std::string folder) {
		std::vector<Folder> lista = process(folder);
		std::string result = "[ ";

		for (unsigned int i = 0; i < lista.size(); i++) {
			Folder item = lista.at(i);

			if (i == 0)
				result += item.toJSON();
			else
				result += ", " + item.toJSON();
		}

		return result + " ]";
	}

	void ProcessFolders::processFoldersToFile(std::string data, const std::string sfile) {
		std::fstream arquivo;
		std::ofstream fs;
		std::string linha;

		fs.open(sfile.c_str(), std::ofstream::out);

		if (fs.is_open()) {
			fs << data;
			fs.close();
		}
	}


	std::string ProcessFolders::processFoldersToInsert(std::string folder, int naba) {
		std::vector<Folder> lista = process(folder);
		std::string result = "";

		for (Folder item : lista) {
			result += item.toInsert(naba) + "\n";
		}

		return result;
	}

	std::string ProcessFolders::processFoldersToCSV(std::string folder) {
		std::vector<Folder> lista = process(folder);
		std::string result = "Code;Order;Name;Size;\"Folder Type\";\"Formated Modified\";Attributes;\"Parent Code Folder\";Path\n";

		for (Folder item : lista) {
			result += item.toCVS() + "\n";
		}

		return result;
	}

}