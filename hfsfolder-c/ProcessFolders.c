#include "ProcessFolders.h"

#include "sys/types.h"
#include "sys/stat.h"
#include "unistd.h"
#include "errno.h"
#include "stdio.h"
#include "stdlib.h"
#include "DateTime.h"
#include "regex.h"

#include "VisitFoldersUtil.h"

#if !defined (S_IWUSR)
	#define S_IWUSR 00200         /* write permission: owner. */
#endif /* !S_IWUSR */

String ProcessFolders_MountBigSize(long double nTam) {
	String fmt;
	String ret = String_iniciar2("");
	long long nUmKilo, nUmMega, nUmGiga, nUmTera, nUmPeta;

	nUmKilo = 1024;
	nUmMega = nUmKilo * nUmKilo;
	nUmGiga = nUmMega * nUmKilo;
	nUmTera = nUmGiga * nUmKilo;
	nUmPeta = nUmTera * nUmKilo;

	if (nTam < nUmKilo) {
		fmt = String_FromLongDouble(nTam);
		ret = String_concatenar4(fmt, " Byte(s)");
		return ret;
	}
	else if (nTam > nUmKilo && nTam < nUmMega) {
		nTam = nTam / nUmKilo;
		fmt = String_FromLongDouble(nTam);
		ret = String_concatenar4(fmt, " KByte(s)");
		return ret;
	}
	else if (nTam > nUmMega && nTam < nUmGiga) {
		nTam = nTam / nUmMega;
		fmt = String_FromLongDouble(nTam);
		ret = String_concatenar4(fmt, " MByte(s)");
		return ret;
	}
	else if (nTam > nUmGiga && nTam < nUmTera) {
		nTam = nTam / nUmGiga;
		fmt = String_FromLongDouble(nTam);
		ret = String_concatenar4(fmt, " GByte(s)");
		return ret;
	}
	else if (nTam > nUmTera && nTam < nUmPeta) {
		nTam = nTam / nUmTera;
		fmt = String_FromLongDouble(nTam);
		ret = String_concatenar4(fmt, " TByte(s)");
		return ret;
	}
	else {
		nTam = nTam / nUmPeta;
		fmt = String_FromLongDouble(nTam);
		ret = String_concatenar4(fmt, " PByte(s)");
		return ret;
	}
}

String ProcessFolders_MountSize(long long nTam) {
	String ret = String_iniciar2("");

	if (nTam > 0) {
		return ProcessFolders_MountBigSize((long double)nTam);
	}
	else {
		return ret;
	}
}

PreFile ProcessFolders_attributesToPreFile(Folder sfile){
	struct stat fileInfo;
	DateTime datahora;
	String sdatetime;
	String sAtributos = String_limpar();
	PreFile preFile;

	String sName = String_copiar4(sfile.preFile.name);
	sName = String_ReplaceAll(sName, "'", "''");
	preFile.name = String_copiar4(sName);
	preFile.originalPath = String_copiar4(sfile.originalPath);

	if (_access(preFile.originalPath.str, 0) == 0) {
		stat(preFile.originalPath.str, &fileInfo);

		datahora = DateTime_raw(fileInfo.st_mtime);

		if ((fileInfo.st_mode & S_IFMT) == S_IFDIR) {
			sAtributos = String_concatenar4(sAtributos, "[DIR]");
			preFile.directory = true;
		}
		else {
			sAtributos = String_concatenar4(sAtributos, "[ARQ]");
			preFile.directory = false;
		}

		//S_IREAD S_IWRITE
		/*
		if ((fileInfo.st_mode & S_IFMT) != S_IWUSR) {
			sAtributos = String_concatenar4(sAtributos, "[ROL]");
		}
		 */

		preFile.size = fileInfo.st_size;
		preFile.modified = datahora;
		preFile.attributes = String_copiar4(sAtributos);
	}
	else {
		preFile.size = 0;
		preFile.modified = DateTime_Now();
		preFile.attributes = String_limpar();
	}

	preFile.formatedSize = ProcessFolders_MountSize(preFile.size);
	DateTime_FormatDateTime(preFile.modified, DateTime_FORMATO_DATAHORA, sdatetime);
	preFile.formatedModified = String_copiar4(sdatetime);

	return preFile;
}

Folder ProcessFolders_createFolder(Folder sfile, FolderOrder *folderOrder){
	regex_t reg, reg2;
	PreFile preFile = ProcessFolders_attributesToPreFile(sfile);
	Folder dir;
	dir.preFile = PreFile_copy(preFile);
	
	if (preFile.directory) {
		dir.folderType = 'D';
	}
	else {
		dir.folderType = 'A';
	}

	String sPath = String_copiar4(preFile.originalPath);

    if (regcomp(&reg, "[a-zA-Z]:\\\\", REG_EXTENDED | REG_NOSUB)==0){
		if (regexec(&reg, sPath.str, 0, 0, 0)==0) {
			sPath =  String_SubString(sPath, 4, sPath.length);
			dir.preFile.separatorChar = '\\';			
		}
	}
    regfree(&reg);

    if (regcomp(&reg2, "[a-zA-Z]:/", REG_EXTENDED | REG_NOSUB)==0){
		if (regexec(&reg2, sPath.str, 0, 0, 0)==0) {
			sPath =  String_SubString(sPath, 4, sPath.length);
			dir.preFile.separatorChar = '/';
		}
	}
    regfree(&reg2);
		
	if (String_cStartsStr("/", sPath.str)) {
		sPath =  String_SubString(sPath, 2, sPath.length);
		dir.preFile.separatorChar = '/';
	}

	sPath = String_ReplaceAll(sPath, "'", "''");
	sPath = String_ReplaceAll(sPath, "\\", "/");

	dir.path = String_copiar4(sPath);
	dir.originalPath = String_copiar4(preFile.originalPath);

	if (!String_cContainsStr(dir.path.str, "/")) {
		folderOrder->codFolder++;
		folderOrder->order = 1;
	}
	else {
		folderOrder->order++;
	}

	dir.code = folderOrder->codFolder;
	dir.order = folderOrder->order;
	
	return dir;
}

bool ProcessFolders_filterFindFirst(FolderList listFolders, String sfolder, Folder *rfolder){
	FolderList local;
	Folder folder;
	
    for (local = listFolders; local != NULL; local = local->next) {
        folder = local->folder;
		
		if (String_comparar1(sfolder, folder.originalPath)) {
			*rfolder = Folder_copy(folder);
			return true;
		}
	}

	return false;
}

FolderList ProcessFolders_process(String folder){
	FolderList listFolders, listaPaths;
	FolderList local;
	Folder dir, item;
	FolderOrder* folderOrder = FolderOrder_new(-1, 0);
	String pathChild;
	Folder* pathFather;
	String sep = String_iniciar1(item.preFile.separatorChar);

	puts("Processing folders!\n");

	listaPaths = VisitFoldersUtil_process(folder.str);

    for (local = listaPaths; local != NULL; local = local->next) {
        item = local->folder;

		dir = ProcessFolders_createFolder(item, folderOrder);
		FolderList_insereFim(&listFolders, dir);
	}

    for (local = listFolders; local != NULL; local = local->next) {
        item = local->folder;

		int nlast = String_cLastDelimiter(sep.str, item.originalPath.str);
		pathChild = String_SubString(item.originalPath, 1, nlast);

		pathFather = Folder_new();

		if (ProcessFolders_filterFindFirst(listFolders, pathChild, pathFather)) {
			item.parentCodFolder = pathFather->order;
			item.parentName = String_copiar4(pathFather->preFile.name);
			item.parentPath = String_copiar4(pathFather->path);
			
			local->folder = Folder_copy(item);
		}
	}

	FolderList_sort(&local);

	return local;
}

String ProcessFolders_processFoldersToJson(String folder){
	FolderList lista = ProcessFolders_process(folder);
	String result = String_iniciar2("[ ");
	FolderList local;
	Folder item;
	unsigned int i = 0;

    for (local = lista; local != NULL; local = local->next) {
        item = local->folder;

		if (i == 0)			
			result = String_concatenar1(result, Folder_toJSON(item));
		else
			result = String_concatenar7(result, 2, ", ", Folder_toJSON(item));
			
		i++;	
	}

	result = String_concatenar4(result, " ]");

	return result;
}

void ProcessFolders_processFoldersToFile(String data, const String sfile){
	FILE *pfile = fopen(sfile.str, "w");

	if(pfile == NULL) {
		printf("Error opening %s for writing.", sfile.str);
	} else {
		fputs(data.str, pfile);
		fclose(pfile);
	}
}

String ProcessFolders_processFoldersToInsert(String folder, int naba){
	FolderList lista = ProcessFolders_process(folder);
	String result = String_limpar();
	FolderList local;
	Folder item;

    for (local = lista; local != NULL; local = local->next) {
        item = local->folder;
		result = String_concatenar5(result, Folder_toInsert(item, naba), "\n");
	}

	return result;
}

String ProcessFolders_processFoldersToCSV(String folder){
	FolderList lista = ProcessFolders_process(folder);
	String result = String_iniciar2("Code;Order;Name;Size;\"Folder Type\";\"Formated Modified\";Attributes;\"Parent Code Folder\";Path\n");
	FolderList local;
	Folder item;

    for (local = lista; local != NULL; local = local->next) {
        item = local->folder;
		result = String_concatenar5(result, Folder_toCVS(item), "\n");
	}

	return result;
}
