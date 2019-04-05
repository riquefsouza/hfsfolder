#include "FolderList.h"
#include "stdbool.h"
#include "Folder.h"
#include "malloc.h"

FolderList FolderList_aloca() 
{
	FolderList ls;
	ls = (FolderList)malloc(sizeof(struct noFolder));

	return(ls);
}

FolderList FolderList_inicia()
{
  return NULL;
}

void FolderList_libera(FolderList ls)
{
	free(ls);
}

void FolderList_insereFim(FolderList *ls, Folder folder)
{
	FolderList local, temp;

	local = FolderList_aloca();
	local->order = 0;
	
	local->folder = Folder_copy(folder);
	
	local->next = NULL;
	if (*ls == NULL)
		*ls = local;
	else {
		/* procura o ulitmo no */
		for (temp = *ls; temp->next != NULL; temp = temp->next);
		local->order = temp->order;
		local->order++;
		temp->next = local;
	}
}

bool FolderList_remove(FolderList ls, Folder *folder)
{
	FolderList local;

	if ((ls == NULL) || (ls->next == NULL)) {
		// remoção nula
		return false;
	}
	local = ls->next;
	
	*folder = Folder_copy(local->folder);
	
	ls->next = local->next;
	FolderList_libera(local);
	return true;
}

void FolderList_arrumaOrdem(FolderList ls)
{
FolderList local;
unsigned int nordem;

  nordem = 0;
  for (local = ls; local != NULL; local = local->next) {
		local->order = nordem;
		nordem++;
  }
}

void FolderList_removeItem(FolderList *ls, Folder folder, bool bArrumaOrdem)
{
	FolderList local, temp;

	Folder localfolder;
	temp = NULL;
	local = *ls;
	while (local != NULL) {
		if (Folder_compare(folder, local->folder)) {
			local = local->next;
			if (temp == NULL){
				/* remove o primeiro no da lista */
				FolderList_libera(*ls);
				*ls = local;
			} else
				FolderList_remove(temp, &localfolder);
		} else {
			temp = local;
			local = local->next;
		}
	}
	if (bArrumaOrdem)
  	FolderList_arrumaOrdem(*ls);
}

void FolderList_removeItemOrd(FolderList *ls, unsigned int ordem, bool bArrumaOrdem)
{
	FolderList local, temp;

	Folder localfolder;
	temp = NULL;
	local = *ls;
	while (local != NULL) {
		if (local->order == ordem){
			local = local->next;
			if (temp == NULL){
				/* remove o primeiro no da lista */
				FolderList_libera(*ls);
				*ls = local;
			} else
				FolderList_remove(temp, &localfolder);
		} else {
			temp = local;
			local = local->next;
		}
	}
	if (bArrumaOrdem)
  	FolderList_arrumaOrdem(*ls);
}

void FolderList_removeTodos(FolderList ls)
{ 
	int ncont, ntotal;
	ntotal = FolderList_conta(ls);
	for (ncont=0; ncont < ntotal; ncont++)
		FolderList_removeItemOrd(&ls, ncont, false);
}

bool FolderList_pesquisaItem(FolderList ls, Folder folder)
{
	FolderList local;

	for (local = ls; local != NULL; local = local->next) {
		if (Folder_compare(local->folder, folder))
			return true;
	}
	return false;
}

Folder* FolderList_pesquisaItemOrd(FolderList ls, unsigned int ordem)
{
	FolderList local;
	Folder *folder = Folder_new();
	
	for (local = ls; local != NULL; local = local->next) {
		if (local->order == ordem)
			return &(local->folder);
	}
	return folder;
}

int FolderList_conta(FolderList ls)
{
	FolderList local;
	int ncont;
	ncont = 0;
	for (local = ls; local != NULL; local = local->next)
		ncont++;

	return ncont;
}

void FolderList_sort(FolderList *ls)
{
	String path1, path2;
	FolderList local;
	Folder folder1, folder2, temp;

	local = *ls;
	
	while (local != NULL) {
		folder1 = local->folder;
		path1 = folder1.path;
		
		if (local->next != NULL){
			folder2 = local->next->folder;
			path2 = folder2.path;
			
			if (strcmp(path1.str, path2.str) > 0) {
				temp = Folder_copy(folder1);
				folder1 = Folder_copy(folder2);
				folder2 = Folder_copy(temp);
				
				local->folder = Folder_copy(folder1);
				local->next->folder = Folder_copy(folder2);
				
				*ls = local;
			}
		}
		
		local = local->next;
	}
}
