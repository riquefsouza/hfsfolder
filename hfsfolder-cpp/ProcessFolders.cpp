#include "ProcessFolders.h"

#include <cstdlib>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <set>

namespace hfsfolder
{
	
ProcessFolders::ProcessFolders()
{
}

ProcessFolders::~ProcessFolders()
{
}

std::string ProcessFolders::LongLongToStr(const long long valor) {
	char *retorno = new char[40];
	std::snprintf(retorno, 40, "%lld", valor);
	return retorno;

	/*
	std::stringstream ss;
	ss.precision(40);
	ss << valor;
	return ss.str();
	*/
}

std::string ProcessFolders::LongDoubleToStr(const long double valor) {
	char *retorno = new char[40];
	std::snprintf(retorno, 40, "%4.2Lf", valor);
	return retorno;

	/*
	std::stringstream ss;
	ss.precision(40);
	ss << valor;
	return ss.str();
	*/
}

std::string ProcessFolders::MontaTamanhoBig(long double nTam) {
	long long nUmKilo, nUmMega, nUmGiga, nUmTera, nUmPeta;

	nUmKilo = 1024;
	nUmMega = nUmKilo * nUmKilo;
	nUmGiga = nUmMega * nUmKilo;
	nUmTera = nUmGiga * nUmKilo;
	nUmPeta = nUmTera * nUmKilo;

	if (nTam < nUmKilo) {
		return LongDoubleToStr(nTam) + " Byte(s)";
	}
	else if (nTam > nUmKilo && nTam < nUmMega) {
		nTam = nTam / nUmKilo;
		return LongDoubleToStr(nTam) + " KByte(s)";
	}
	else if (nTam > nUmMega && nTam < nUmGiga) {
		nTam = nTam / nUmMega;
		return LongDoubleToStr(nTam) + " MByte(s)";
	}
	else if (nTam > nUmGiga && nTam < nUmTera) {
		nTam = nTam / nUmGiga;
		return LongDoubleToStr(nTam) + " GByte(s)";
	}
	else if (nTam > nUmTera && nTam < nUmPeta) {
		nTam = nTam / nUmTera;
		return LongDoubleToStr(nTam) + " TByte(s)";
	}
	else {
		nTam = nTam / nUmPeta;
		return LongDoubleToStr(nTam) + " PByte(s)";
	}
}

std::string ProcessFolders::MontaTamanho(long long nTam) {
	if (nTam > 0) {
		return MontaTamanhoBig((long double)nTam);
	}
	else {
		return "";
	}
}

PreFile ProcessFolders::attributesToPreFile(path sfile){
	struct stat fileInfo;
	ptime datahora;
	std::string sAtributos = "";
	PreFile preFile;
	
	preFile.setName(sfile.leaf().string());
	preFile.setOriginalPath(sfile.string());

	if (_access(preFile.getOriginalPath().c_str(), 0) == 0) {
		stat(preFile.getOriginalPath().c_str(), &fileInfo);

		datahora = from_time_t(fileInfo.st_mtime);

		if ((fileInfo.st_mode & S_IFMT) == S_IFDIR) {
			sAtributos += "[DIR]";
			preFile.setDirectory(true);
		} else {
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
	
	return preFile;
}

std::string ProcessFolders::replaceAll(const std::string texto,
	const std::string velho, const std::string novo) {
	std::string stexto = texto;
	size_t pos = 0;
	while ((pos = stexto.find(velho, pos)) != std::string::npos)
	{
		stexto.replace(pos, velho.length(), novo);
		pos += novo.length();
	}
	return stexto;
}

bool ProcessFolders::startsWith(const std::string texto, const std::string subtexto) {
	return subtexto.length() <= texto.length()
		&& std::equal(subtexto.begin(), subtexto.end(), texto.begin());
}

int ProcessFolders::pos(const std::string subtexto, const std::string texto) {
	std::string::size_type loc = texto.find(subtexto, 0);
	if (loc != std::string::npos)
		return (loc + 1);
	else
		return -1;
}

bool ProcessFolders::contains(const std::string texto, const std::string subtexto) {
	return (pos(subtexto, texto) > 0);
}

int ProcessFolders::lastIndexOf(const std::string texto, const char subtexto) {
	std::string::size_type loc = texto.find_last_of(subtexto);
	if (loc != std::string::npos)
		return (loc + 1);
	else
		return -1;
}

Folder ProcessFolders::createFolder(path sfile, FolderOrder *folderOrder) {
	PreFile preFile = attributesToPreFile(sfile);
	Folder dir = new Folder(&preFile);

	if (preFile.isDirectory()) {
		dir.setFolderType('D');
	} else {						
		dir.setFolderType('A');			
	}
	
	std::string sPath = preFile.getOriginalPath();
		
	boost::regex pattern("[a-zA-Z]:\\\\");
	if (regex_match(sPath, pattern)) {
		sPath = sPath.substr(3);
	}
	
	if (startsWith(sPath, "/")) {
		sPath = sPath.substr(1);
		preFile.separatorChar = '/';
	} else {
		preFile.separatorChar = '\\';
	}
	
	sPath = replaceAll(sPath, "'", "''");
	sPath = replaceAll(sPath, "\\\\", "/");
	dir.setPath(sPath);
	dir.setOriginalPath(preFile.getOriginalPath());

	if (!contains(dir.getPath(), "/")) {
		folderOrder->setCodFolder(folderOrder->getCodFolder()+1);
		folderOrder->setOrder(1);
	} else {
		folderOrder->setOrder(folderOrder->getOrder()+1);	
	}

	dir.setCode(folderOrder->getCodFolder());
	dir.setOrder(folderOrder->getOrder());

	return dir;
}

bool ProcessFolders::filterFindFirst(std::vector<Folder> listFolders, const std::string sfolder, Folder *rfolder) {
	
	for (unsigned int i = 0; i < listFolders.size(); i++) {
		Folder folder = listFolders.at(i);
		
		if (std::equal(sfolder.begin(), sfolder.end(), folder.getOriginalPath().begin())){
			rfolder = &folder;
			return true;
		}
	}
	
	return false;
}

std::vector<Folder> ProcessFolders::process(std::string folder) {
	std::vector<Folder> listFolders;
	Folder dir;
	FolderOrder *folderOrder = new FolderOrder(-1, 0);

	std::cout << "Processing folders!" << std::endl;
	
	std::vector<path> listaPaths = VisitFoldersUtil::getPathsFromFiles(folder);
	
	for (unsigned int i = 0; i < listaPaths.size(); i++) {
		path spath = listaPaths.at(i);
		
		dir = createFolder(spath, folderOrder);
		listFolders.push_back(dir);
	}
	
	for (unsigned int i = 0; i < listFolders.size(); i++) {
		Folder item = listFolders.at(i);
		
		std::string pathChild = item.getOriginalPath().substr(0, 
				lastIndexOf(item.getOriginalPath(), item.separatorChar));
		
		Folder pathFather;
				
		if (filterFindFirst(listFolders, pathChild, &pathFather)) {
			item.setParentCodFolder(pathFather.getOrder());
			item.setParentName(pathFather.getName());
			item.setParentPath(pathFather.getPath());
		}
	}
	
	return listFolders;
}
	
std::string ProcessFolders::processFoldersToJson(std::string folder) {
	JSONListConverter<Folder> jsonFolders = new JSONListConverter<Folder>();
	std::vector<Folder> lista = process(folder);
	
	return jsonFolders.listaToJSON(lista);
}

void ProcessFolders::processFoldersToFile(std::string data, std::string file) {
	try {
		Files.write(Paths.get(file), data.getBytes());
	} catch (IOException e) {
		log.error(e);
	}
}
	
std::string ProcessFolders::processFoldersToInsert(std::string folder, int naba) {
	std::vector<Folder> lista = process(folder);
	std::string result = "";
	
	for (Folder item : lista) {
		result += item.toInsert(naba)+"\n";
	}

	return result;
}

std::string ProcessFolders::processFoldersToCSV(std::string folder) {
	std::vector<Folder> lista = process(folder);
	std::string result = "Code;Order;Name;Size;\"Folder Type\";\"Formated Modified\";Attributes;\"Parent Code Folder\";Path\n";
	
	for (Folder item : lista) {
		result += item.toCVS()+"\n";
	}

	return result;
}
	
}