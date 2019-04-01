#ifndef FolderList_H
#define FolderList_H

#pragma once

#include "stdafx.h"

#include "Folder.h"

struct noFolder {
	unsigned int order;
	Folder folder;
	struct noFolder *next;
};
typedef struct noFolder *FolderList;

FolderList FolderList_aloca();
FolderList FolderList_inicia();
VOID FolderList_libera(FolderList ls);
VOID FolderList_insereFim(FolderList *ls, Folder folder);
BOOL FolderList_remove(FolderList ls, Folder *folder;
VOID FolderList_arrumaOrdem(FolderList ls);
VOID FolderList_removeItem(FolderList *ls, Folder folder, BOOL bArrumaOrdem);
VOID FolderList_removeItemOrd(FolderList *ls, UINT ordem, BOOL bArrumaOrdem);
VOID FolderList_removeTodos(FolderList ls);
BOOL FolderList_pesquisaItem(FolderList ls, Folder folder);
LPTSTR FolderList_pesquisaItemOrd(FolderList ls, UINT ordem);
INT FolderList_conta(FolderList ls);

#endif


