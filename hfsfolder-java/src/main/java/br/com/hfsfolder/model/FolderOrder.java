/**
 * @author Henrique Figueiredo de Souza
 * @version 1.0
 * @since 2019
 */
package br.com.hfsfolder.model;

/**
 * The Class FolderOrder.
 */
public class FolderOrder {

	/** The cod folder. */
	private int codFolder;
	
	/** The ordem. */
	private int order;
	
	/**
	 * Instantiates a new folder order.
	 *
	 * @param codFolder the cod folder
	 * @param ordem the ordem
	 */
	public FolderOrder(int codFolder, int order) {
		super();
		this.codFolder = codFolder;
		this.order = order;
	}
	
	/**
	 * Instantiates a new folder order.
	 *
	 * @param folderOrder the folder order
	 */
	public FolderOrder(FolderOrder folderOrder) {
		super();
		this.codFolder = folderOrder.getCodFolder();
		this.order = folderOrder.getOrder();
	}
	
	/**
	 * Gets the cod folder.
	 *
	 * @return the cod folder
	 */
	public int getCodFolder() {
		return codFolder;
	}

	/**
	 * Sets the cod folder.
	 *
	 * @param codFolder the new cod folder
	 */
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
