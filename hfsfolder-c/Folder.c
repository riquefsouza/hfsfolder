#include "Folder.h"
#include "malloc.h"
#include "StringUtil.h"

Folder* Folder_new() {
	Folder *folder;
	folder = (Folder*)malloc(sizeof(struct SFolder));

	return(folder);
}

Folder Folder_copy(Folder folder) {
	Folder lfolder;

	lfolder.preFile.name = String_copiar4(folder.preFile.name);
	lfolder.preFile.size = folder.preFile.size;
	lfolder.preFile.modified = DateTime_copiar(folder.preFile.modified);
	lfolder.preFile.attributes = String_copiar4(folder.preFile.attributes);
	lfolder.preFile.formatedSize = String_copiar4(folder.preFile.formatedSize);
	lfolder.preFile.formatedModified = String_copiar4(folder.preFile.formatedModified);
	lfolder.preFile.originalPath = String_copiar4(folder.preFile.originalPath);
	lfolder.preFile.directory = folder.preFile.directory;
	lfolder.code = folder.code;
	lfolder.order = folder.order;
	lfolder.parentCodFolder = folder.parentCodFolder;
	lfolder.folderType = folder.folderType;
	lfolder.path = String_copiar4(folder.path);
	lfolder.parentName = String_copiar4(folder.parentName);
	lfolder.parentPath = String_copiar4(folder.parentPath);
	
	return lfolder;
}

bool Folder_compare(Folder folder1, Folder folder2) {
	return (		
	String_comparar1(folder1.preFile.name, folder2.preFile.name)
	&& folder1.preFile.size == folder2.preFile.size
	&& DateTime_comparar(folder1.preFile.modified, folder2.preFile.modified)
	&& String_comparar1(folder1.preFile.attributes, folder2.preFile.attributes)
	&& String_comparar1(folder1.preFile.formatedSize, folder2.preFile.formatedSize)
	&& String_comparar1(folder1.preFile.formatedModified, folder2.preFile.formatedModified)
	&& String_comparar1(folder1.preFile.originalPath, folder2.preFile.originalPath)
	&& folder1.preFile.directory == folder2.preFile.directory
	&& folder1.code == folder2.code
	&& folder1.order == folder2.order
	&& folder1.parentCodFolder == folder2.parentCodFolder
	&& folder1.folderType == folder2.folderType
	&& String_comparar1(folder1.path, folder2.path)
	&& String_comparar1(folder1.parentName, folder2.parentName)
	&& String_comparar1(folder1.parentPath, folder2.parentPath)	
	);
}

void Folder_limparDados(Folder folder) {
    PreFile_limparDados(folder.preFile);
    folder.code = 0;
    folder.order = 0;
    folder.parentCodFolder = 0;
    folder.folderType = 'A';
    folder.path = String_limpar();
    folder.parentName = String_limpar();
    folder.parentPath = String_limpar();
    folder.originalPath = String_limpar();
}

String Folder_toString(Folder folder) {
	String str = String_iniciar2("Folder [codigo=");
	str = String_concatenar5(str, String_FromInt(folder.code), ", ordem=");
	str = String_concatenar5(str, String_FromInt(folder.order), ", codDirPai=");
	str = String_concatenar5(str, String_FromInt(folder.parentCodFolder), ", tipo=");
	str = String_concatenar5(str, String_QuotedStr2(folder.folderType), ", caminho=");
	str = String_concatenar5(str, String_QuotedStr1(folder.path), ", nomePai=");
	str = String_concatenar5(str, String_QuotedStr1(folder.parentName), ", caminhoPai=");
	str = String_concatenar5(str, String_QuotedStr1(folder.parentPath), "]");	
    return str;
}

String Folder_toInsert(Folder folder, int naba) {
	String str = String_iniciar2("INSERT INTO Diretorios(aba, cod, ordem, nome, tam, tipo, modificado, atributos, coddirpai, caminho) VALUES(");
	str = String_concatenar5(str, String_FromInt(naba), ",");
	str = String_concatenar5(str, String_FromInt(folder.code), ",");
	str = String_concatenar5(str, String_FromInt(folder.order), ",'");
	str = String_concatenar5(str, String_QuotedStr1(folder.preFile.name), "',");
	str = String_concatenar5(str, String_FromLongLong(folder.preFile.size), ",'");
	str = String_concatenar5(str, String_QuotedStr2(folder.folderType), "','");
	str = String_concatenar5(str, String_QuotedStr1(folder.preFile.formatedModified), "','");
	str = String_concatenar5(str, String_QuotedStr1(folder.preFile.attributes), "',");	
	str = String_concatenar5(str, String_FromInt(folder.parentCodFolder), ",'");
	str = String_concatenar5(str, String_QuotedStr1(folder.path), "');");
	return str;		
}

String Folder_toCVS(Folder folder) {
	String str = String_iniciar2("");
	str = String_concatenar5(str, String_FromInt(folder.code), ";");
	str = String_concatenar5(str, String_FromInt(folder.order), ";");
	str = String_concatenar5(str, String_QuotedStr1(folder.preFile.name), ";");
	str = String_concatenar5(str, String_FromLongLong(folder.preFile.size), ";");
	str = String_concatenar5(str, String_QuotedStr2(folder.folderType), ";");
	str = String_concatenar5(str, String_QuotedStr1(folder.preFile.formatedModified), ";");
	str = String_concatenar5(str, String_QuotedStr1(folder.preFile.attributes), ";");	
	str = String_concatenar5(str, String_FromInt(folder.parentCodFolder), ";");
	str = String_concatenar5(str, String_QuotedStr1(folder.path), "");
	return str;
}

String Folder_toJSON(Folder folder) {
	String sdatetime;
	String str = String_iniciar2("{\n  \"name\" : \"");
	str = String_concatenar5(str, String_QuotedStr1(folder.preFile.name), "\",\n  \"size\" : ");
	str = String_concatenar5(str, String_FromLongLong(folder.preFile.size), ",\n  \"modified\" : ");	
	DateTime_FormatDateTime(folder.preFile.modified, DateTime_FORMATO_DATAHORA, sdatetime);
	str = String_concatenar5(str, String_QuotedStr1(sdatetime), ",\n  \"attributes\" : \"");
	str = String_concatenar5(str, String_QuotedStr1(folder.preFile.attributes), "\",\n  \"formatedSize\" : \"");
	str = String_concatenar5(str, String_QuotedStr1(folder.preFile.formatedSize), "\",\n  \"formatedModified\" : \"");
	str = String_concatenar5(str, String_QuotedStr1(folder.preFile.formatedModified), "\",\n  \"code\" : ");
	str = String_concatenar5(str, String_FromInt(folder.code), ",\n  \"order\" : ");
	str = String_concatenar5(str, String_FromInt(folder.order), ",\n  \"parentCodFolder\" : ");
	str = String_concatenar5(str, String_FromInt(folder.parentCodFolder), ",\n  \"folderType\" : \"");
	str = String_concatenar5(str, String_QuotedStr2(folder.folderType), "\",\n  \"path\" : \"");
	str = String_concatenar5(str, String_QuotedStr1(folder.path), "\",\n  \"parentName\" : \"");
	str = String_concatenar5(str, String_QuotedStr1(folder.parentName), "\",\n  \"parentPath\" : \"");
	str = String_concatenar5(str, String_QuotedStr1(folder.parentPath), "\",\n  \"originalPath\" : \"");	
	str = String_concatenar5(str, String_QuotedStr1(folder.preFile.originalPath), "\"\n}");		
	return str;
}