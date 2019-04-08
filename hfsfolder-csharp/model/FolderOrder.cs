/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 08/04/2019
 * Time: 13:52
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;

namespace hfsfolder.model
{
	/// <summary>
	/// Description of FolderOrder.
	/// </summary>
	public class FolderOrder
	{
		private int codFolder;
		
		private int order;
		
		public FolderOrder(int codFolder, int order) {
			this.codFolder = codFolder;
			this.order = order;
		}
		
		public FolderOrder(FolderOrder folderOrder) {
			this.codFolder = folderOrder.getCodFolder();
			this.order = folderOrder.getOrder();
		}
		
		public int getCodFolder() {
			return codFolder;
		}
	
		public void setCodFolder(int codFolder) {
			this.codFolder = codFolder;
		}
	
		public int getOrder() {
			return order;
		}
	
		public void setOrder(int order) {
			this.order = order;
		}
	
	}
}
