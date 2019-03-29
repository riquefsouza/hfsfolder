#ifndef FolderList_H
#define FolderList_H

/*
 * @author Henrique Figueiredo de Souza
 * @version 1.0
 * @since 2019
 */

struct noFolder {
	unsigned int order;
	Folder folder;
	struct noFolder *next;
};
typedef struct nostr *FolderList;

FolderList FolderList_aloca();
FolderList FolderList_inicia();
VOID FolderList_libera(FolderList ls);
VOID FolderList_insereFim(FolderList *ls, LPTSTR str);
BOOL FolderList_remove(FolderList ls, LPTSTR *str);
VOID FolderList_arrumaOrdem(FolderList ls);
VOID FolderList_removeItem(FolderList *ls, LPTSTR str, BOOL bArrumaOrdem);
VOID FolderList_removeItemOrd(FolderList *ls, UINT ordem, BOOL bArrumaOrdem);
VOID FolderList_removeTodos(FolderList ls);
BOOL FolderList_pesquisaItem(FolderList ls, LPTSTR str);
LPTSTR FolderList_pesquisaItemOrd(FolderList ls, UINT ordem);
INT FolderList_conta(FolderList ls);

#endif


