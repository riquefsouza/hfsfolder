#include "stdafx.h"

#include "FolderList.h"

FolderList FolderList_aloca()
{
	FolderList ls;
	ls = (FolderList) GlobalAlloc(GPTR, sizeof(struct noFolder));

	return(ls);
}

FolderList FolderList_inicia()
{
  return NULL;
}

VOID FolderList_libera(FolderList ls)
{
	GlobalFree(ls);
}

VOID FolderList_insereFim(FolderList *ls, Folder folder)
{
	FolderList local, temp;

	local = FolderList_aloca();
	local->ordem = 0;
	
	local->folder = Folder_copy(folder);
	
	local->proximo = NULL;
	if (*ls == NULL)
		*ls = local;
	else {
		/* procura o ulitmo no */
		for (temp = *ls; temp->proximo != NULL; temp = temp->proximo);
    local->ordem = temp->ordem;
    local->ordem++;
		temp->proximo = local;
	}
}

BOOL FolderList_remove(FolderList ls, Folder *folder)
{
	FolderList local;

	if ((ls == NULL) || (ls->proximo == NULL)) {
		// remoção nula
		return FALSE;
	}
	local = ls->proximo;
	
	*folder = Folder_copy(local->folder);
	
	ls->proximo = local->proximo;
	FolderList_libera(local);
	return TRUE;
}

VOID FolderList_arrumaOrdem(FolderList ls)
{
FolderList local;
UINT nordem;

  nordem = 0;
  for (local = ls; local != NULL; local = local->proximo) {
		local->ordem = nordem;
		nordem++;
  }
}

VOID FolderList_removeItem(FolderList *ls, Folder folder, BOOL bArrumaOrdem)
{
	FolderList local, temp;

	LPTSTR localstr;
	temp = NULL;
	local = *ls;
	while (local != NULL) {
		if (Folder_compare(folder, local->folder)) {
			local = local->proximo;
			if (temp == NULL){
				/* remove o primeiro no da lista */
				FolderList_libera(*ls);
				*ls = local;
			} else
				FolderList_remove(temp, &localstr);
		} else {
			temp = local;
			local = local->proximo;
		}
	}
	if (bArrumaOrdem)
  	FolderList_arrumaOrdem(*ls);
}

VOID FolderList_removeItemOrd(FolderList *ls, UINT ordem, BOOL bArrumaOrdem)
{
	FolderList local, temp;

	LPTSTR localstr;
	temp = NULL;
	local = *ls;
	while (local != NULL) {
		if (local->ordem == ordem){
			local = local->proximo;
			if (temp == NULL){
				/* remove o primeiro no da lista */
				FolderList_libera(*ls);
				*ls = local;
			} else
				FolderList_remove(temp, &localstr);
		} else {
			temp = local;
			local = local->proximo;
		}
	}
	if (bArrumaOrdem)
  	FolderList_arrumaOrdem(*ls);
}

VOID FolderList_removeTodos(FolderList ls)
{ 
	INT ncont, ntotal;
  ntotal = FolderList_conta(ls);
  for (ncont=0; ncont < ntotal; ncont++)
    FolderList_removeItemOrd(&ls, ncont, FALSE);
}

BOOL FolderList_pesquisaItem(FolderList ls, Folder folder)
{
	FolderList local;

	for (local = ls; local != NULL; local = local->proximo) {
		if (Folder_compare(local->folder, folder))
			return TRUE;
	}
	return FALSE;
}

LPTSTR FolderList_pesquisaItemOrd(FolderList ls, UINT ordem)
{
	FolderList local;
	Folder *folder = Folder_new();
	
	for (local = ls; local != NULL; local = local->proximo) {
		if (local->ordem == ordem)
			return local->str;
	}
	return folder;
}

INT FolderList_conta(FolderList ls)
{
	FolderList local;
	INT ncont;
	ncont = 0;
	for (local = ls; local != NULL; local = local->proximo)
		ncont++;

	return ncont;
}
