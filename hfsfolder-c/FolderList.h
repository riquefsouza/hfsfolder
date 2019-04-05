#ifndef FolderList_H
#define FolderList_H

#pragma once

#include "stdbool.h"
#include "Folder.h"

struct noFolder {
	unsigned int order;
	Folder folder;
	struct noFolder *next;
};
typedef struct noFolder *FolderList;

FolderList FolderList_aloca();
FolderList FolderList_inicia();
void FolderList_libera(FolderList ls);
void FolderList_insereFim(FolderList *ls, Folder folder);
bool FolderList_remove(FolderList ls, Folder *folder);
void FolderList_arrumaOrdem(FolderList ls);
void FolderList_removeItem(FolderList *ls, Folder folder, bool bArrumaOrdem);
void FolderList_removeItemOrd(FolderList *ls, unsigned int ordem, bool bArrumaOrdem);
void FolderList_removeTodos(FolderList ls);
bool FolderList_pesquisaItem(FolderList ls, Folder folder);
Folder* FolderList_pesquisaItemOrd(FolderList ls, unsigned int ordem);
int FolderList_conta(FolderList ls);
void FolderList_sort(FolderList *ls);

#endif


