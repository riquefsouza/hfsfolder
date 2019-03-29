#pragma once

namespace hfsfolder_model
{

class FolderOrder
{
	private:
		int codFolder;
		int order;
	
	public:
		FolderOrder();
		FolderOrder(int codFolder, int order);
		FolderOrder(FolderOrder *folderOrder);
		virtual ~FolderOrder();
		
		int getCodFolder();
		void setCodFolder(int codFolder);
		int getOrder();
		void setOrder(int order);
};

}

