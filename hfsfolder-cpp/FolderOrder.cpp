#include "FolderOrder.h"

namespace hfsfolder_model
{
	
FolderOrder::FolderOrder()
{
}

FolderOrder::~FolderOrder()
{
}

FolderOrder::FolderOrder(int codFolder, int order) {
	this->codFolder = codFolder;
	this->order = order;
}

FolderOrder::FolderOrder(FolderOrder *folderOrder) {
	this->codFolder = folderOrder->getCodFolder();
	this->order = folderOrder->getOrder();
}

int FolderOrder::getCodFolder() {
	return codFolder;
}

void FolderOrder::setCodFolder(int codFolder) {
	this->codFolder = codFolder;
}

int FolderOrder::getOrder() {
	return order;
}

void FolderOrder::setOrder(int order) {
	this->order = order;
}

}
