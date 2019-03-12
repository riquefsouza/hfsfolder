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
	private int ordem;
	
	/**
	 * Instantiates a new folder order.
	 *
	 * @param codFolder the cod folder
	 * @param ordem the ordem
	 */
	public FolderOrder(int codFolder, int ordem) {
		super();
		this.codFolder = codFolder;
		this.ordem = ordem;
	}
	
	/**
	 * Instantiates a new folder order.
	 *
	 * @param folderOrder the folder order
	 */
	public FolderOrder(FolderOrder folderOrder) {
		super();
		this.codFolder = folderOrder.getCodFolder();
		this.ordem = folderOrder.getOrdem();
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

	/**
	 * Gets the ordem.
	 *
	 * @return the ordem
	 */
	public int getOrdem() {
		return ordem;
	}

	/**
	 * Sets the ordem.
	 *
	 * @param ordem the new ordem
	 */
	public void setOrdem(int ordem) {
		this.ordem = ordem;
	}

}
