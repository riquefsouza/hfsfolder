/**
 * @author Henrique Figueiredo de Souza
 * @version 1.0
 * @since 2019
 */
package br.com.hfsfolder.model;

/**
 * The Class Folder.
 */
public class Folder extends PreFile {

	/** The codigo. */
	private int code;

	/** The ordem. */
	private int order;

	/** The cod dir pai. */
	private int parentCodFolder;

	/** The tipo. */
	private char folderType;

	/** The caminho. */
	private String path;

	/** The nome pai. */
	private String parentName;

	/** The caminho pai. */
	private String parentPath;

	private String originalPath;

	/**
	 * Instantiates a new folder.
	 *
	 * @param preFile the pre file
	 */
	public Folder(PreFile preFile) {
		super(preFile.getName(), preFile.getSize(), preFile.getModified(), preFile.getAttributes(),
				preFile.getFormatedSize(), preFile.getFormatedModified());
	}

	public int getCode() {
		return code;
	}

	public void setCode(int code) {
		this.code = code;
	}

	public int getOrder() {
		return order;
	}

	public void setOrder(int order) {
		this.order = order;
	}

	public int getParentCodFolder() {
		return parentCodFolder;
	}

	public void setParentCodFolder(int parentCodFolder) {
		this.parentCodFolder = parentCodFolder;
	}

	public char getFolderType() {
		return folderType;
	}

	public void setFolderType(char folderType) {
		this.folderType = folderType;
	}

	public String getPath() {
		return path;
	}

	public void setPath(String path) {
		this.path = path;
	}

	public String getParentName() {
		return parentName;
	}

	public void setParentName(String parentName) {
		this.parentName = parentName;
	}

	public String getParentPath() {
		return parentPath;
	}

	public void setParentPath(String parentPath) {
		this.parentPath = parentPath;
	}

	public String getOriginalPath() {
		return originalPath;
	}

	public void setOriginalPath(String originalPath) {
		this.originalPath = originalPath;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see br.com.hfsfolder.model.PreFile#limparDados()
	 */
	@Override
	public void limparDados() {
		super.limparDados();
		this.code = 0;
		this.order = 0;
		this.parentCodFolder = 0;
		this.folderType = 'A';
		this.path = "";
		this.parentName = "";
		this.parentPath = "";
		this.originalPath = "";
	}

	@Override
	public String toString() {
		return "Folder [codigo=" + code + ", ordem=" + order + ", codDirPai=" + parentCodFolder + ", tipo=" + folderType
				+ ", caminho=" + path + ", nomePai=" + parentName + ", caminhoPai=" + parentPath + "]";
	}

	public String toInsert(int naba) {
		return "INSERT INTO Diretorios(aba, cod, ordem, nome, tam, tipo, modificado, atributos, coddirpai, caminho) VALUES("
				+ naba + "," + code + "," + order + ",'" + getName() + "'," + getSize() + ",'" + folderType + "','"
				+ getFormatedModified() + "','" + getAttributes() + "'," + parentCodFolder + ",'" + getPath()
				+ "');";
	}

	public String toCVS() {
		return code + ";" + order + ";" + getName() + ";" + getSize() + ";" + folderType + ";" 
				+ getFormatedModified() + ";" + getAttributes() + ";" + parentCodFolder + ";" + getPath(); 
	}
}
