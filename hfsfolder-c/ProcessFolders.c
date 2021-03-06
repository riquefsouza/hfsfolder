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

PreFile ProcessFolders_attributesToPreFile(Folder folder){
	String sdatetime = String_limpar();

	folder.preFile.formatedSize = ProcessFolders_MountSize(folder.preFile.size);
	DateTime_FormatDateTime(folder.preFile.modified, DateTime_FORMATO_DATAHORA, sdatetime);
	folder.preFile.formatedModified = String_copiar4(sdatetime);

	return folder.preFile;
}

Folder ProcessFolders_createFolder(Folder sfile, FolderOrder *folderOrder){
	regex_t reg, reg2;
	PreFile preFile = ProcessFolders_attributesToPreFile(sfile);
	Folder dir;
	
	Folder_limparDados(dir);
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
	dir.preFile.originalPath = String_copiar4(preFile.originalPath);

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
	
	Folder_limparDados(folder);
	
    for (local = listFolders; local != NULL; local = local->next) {
        folder = local->folder;
		
		if (String_comparar1(sfolder, folder.preFile.originalPath)) {
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
	String sep;

	Folder_limparDados(dir);
	Folder_limparDados(item);

	puts("Processing folders!\n");

	listaPaths = VisitFoldersUtil_process(folder.str);

    for (local = listaPaths; local != NULL; local = local->next) {
        item = local->folder;

		dir = ProcessFolders_createFolder(item, folderOrder);
		FolderList_insereFim(&listFolders, dir);
	}

    for (local = listFolders; local != NULL; local = local->next) {
        item = local->folder;

		sep = String_iniciar1(item.preFile.separatorChar);
		int nlast = String_cLastDelimiter(sep.str, item.preFile.originalPath.str);
		pathChild = String_SubString(item.preFile.originalPath, 1, nlast);

		pathFather = Folder_new();

		if (ProcessFolders_filterFindFirst(listFolders, pathChild, pathFather)) {
			item.parentCodFolder = pathFather->order;
			item.parentName = String_copiar4(pathFather->preFile.name);
			item.parentPath = String_copiar4(pathFather->path);
			
			local->folder = Folder_copy(item);
		}
	}

	//FolderList_sort(&listFolders);

	return listFolders;
}

StringList ProcessFolders_processFoldersToJson(String folder){
	FolderList lista = ProcessFolders_process(folder);
	String result = String_iniciar2("[ ");
	FolderList local;
	Folder item;
	StringList strList;
	unsigned int i = 0;
	
	Folder_limparDados(item);

	StringList_insereFim(&strList, result);
	
    for (local = lista; local != NULL; local = local->next) {
        item = local->folder;

		if (i == 0)			
			result = Folder_toJSON(item);
		else
			result = String_concatenar6(", ", Folder_toJSON(item));
			
		i++;
			
		StringList_insereFim(&strList, result);
	}

	result = String_copiar1(" ]");
	
	StringList_insereFim(&strList, result);

	return strList;
}

void ProcessFolders_processFoldersToFile(StringList data, const String sfile){	
	StringList local;
	FILE *pfile = fopen(sfile.str, "w");

	if(pfile == NULL) {
		printf("Error opening %s for writing.", sfile.str);
	} else {
		for (local = data; local != NULL; local = local->next) {
			fputs(local->str.str, pfile);
		}
		fclose(pfile);
	}
}

StringList ProcessFolders_processFoldersToInsert(String folder, int naba){
	FolderList lista = ProcessFolders_process(folder);
	String result = String_limpar();
	FolderList local;
	Folder item;
	StringList strList;
	
	Folder_limparDados(item);

    for (local = lista; local != NULL; local = local->next) {
        item = local->folder;
		result = String_concatenar4(Folder_toInsert(item, naba), "\n");
		
		StringList_insereFim(&strList, result);
	}

	return strList;
}

StringList ProcessFolders_processFoldersToCSV(String folder){
	FolderList lista = ProcessFolders_process(folder);
	String result = String_iniciar2("Code;Order;Name;Size;\"Folder Type\";\"Formated Modified\";Attributes;\"Parent Code Folder\";Path\n");
	FolderList local;
	Folder item;
	StringList strList;
	
	Folder_limparDados(item);

	StringList_insereFim(&strList, result);

    for (local = lista; local != NULL; local = local->next) {
        item = local->folder;
		result = String_concatenar4(Folder_toCVS(item), "\n");
		
		StringList_insereFim(&strList, result);
	}

	return strList;
}
