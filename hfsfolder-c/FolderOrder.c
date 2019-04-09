#include "FolderOrder.h"
#include "malloc.h"

FolderOrder* FolderOrder_new(){
	FolderOrder *folderOrder;
	folderOrder = (FolderOrder*)malloc(sizeof(struct SFolderOrder));

	return(folderOrder);
}

FolderOrder* FolderOrder_new2(int codFolder, int order){
	FolderOrder *folderOrder = FolderOrder_new();
	folderOrder->codFolder = codFolder;
	folderOrder->order = order;
	
	return(folderOrder);
}

