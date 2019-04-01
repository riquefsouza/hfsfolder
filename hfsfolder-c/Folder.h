#ifndef Folder_H
#define Folder_H

#pragma once

#include "stdafx.h"

#include "PreFile.h"

struct SFolder {
    PreFile preFile;
	int code;
	int order;
	int parentCodFolder;
	char folderType;
	String path;
	String parentName;
	String parentPath;
	String originalPath;
};

typedef struct SFolder Folder;

Folder* Folder_new();
Folder Folder_copiar(Folder folder);
BOOL Folder_comparar(Folder folder1, Folder folder2);

void Folder_limparDados(Folder folder);
String Folder_toString(Folder folder);
String Folder_toInsert(Folder folder, int naba);
String Folder_toCVS(Folder folder);
String Folder_toJSON(Folder folder);

#endif // Folder_H
