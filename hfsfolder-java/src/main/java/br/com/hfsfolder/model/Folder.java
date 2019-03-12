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
	private int codigo;
	
	/** The ordem. */
	private int ordem;
	
	/** The cod dir pai. */
	private int codDirPai;
	
	/** The tipo. */
	private char tipo;
	
	/** The caminho. */
	private String caminho;
	
	/** The nome pai. */
	private String nomePai;
	
	/** The caminho pai. */
	private String caminhoPai;
	
	private String caminhoOriginal;

	/**
	 * Instantiates a new folder.
	 *
	 * @param preFile the pre file
	 */
	public Folder(PreFile preFile) {
		super(preFile.getNome(), preFile.getTamanho(), preFile.getModificado(), preFile.getAtributos(),
				preFile.getTamanhoFormatado(), preFile.getModificadoFormatado());
	}

	/**
	 * Gets the codigo.
	 *
	 * @return the codigo
	 */
	public int getCodigo() {
		return codigo;
	}

	/**
	 * Sets the codigo.
	 *
	 * @param codigo the codigo to set
	 */
	public void setCodigo(int codigo) {
		this.codigo = codigo;
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
	 * @param ordem the ordem to set
	 */
	public void setOrdem(int ordem) {
		this.ordem = ordem;
	}

	/**
	 * Gets the cod dir pai.
	 *
	 * @return the codDirPai
	 */
	public int getCodDirPai() {
		return codDirPai;
	}

	/**
	 * Sets the cod dir pai.
	 *
	 * @param codDirPai the codDirPai to set
	 */
	public void setCodDirPai(int codDirPai) {
		this.codDirPai = codDirPai;
	}

	/**
	 * Gets the tipo.
	 *
	 * @return the tipo
	 */
	public char getTipo() {
		return tipo;
	}

	/**
	 * Sets the tipo.
	 *
	 * @param tipo the tipo to set
	 */
	public void setTipo(char tipo) {
		this.tipo = tipo;
	}

	/**
	 * Gets the caminho.
	 *
	 * @return the caminho
	 */
	public String getCaminho() {
		return caminho;
	}

	/**
	 * Sets the caminho.
	 *
	 * @param caminho the caminho to set
	 */
	public void setCaminho(String caminho) {
		this.caminho = caminho;
	}

	/**
	 * Gets the nome pai.
	 *
	 * @return the nomePai
	 */
	public String getNomePai() {
		return nomePai;
	}

	/**
	 * Sets the nome pai.
	 *
	 * @param nomePai the nomePai to set
	 */
	public void setNomePai(String nomePai) {
		this.nomePai = nomePai;
	}

	/**
	 * Gets the caminho pai.
	 *
	 * @return the caminhoPai
	 */
	public String getCaminhoPai() {
		return caminhoPai;
	}

	/**
	 * Sets the caminho pai.
	 *
	 * @param caminhoPai the caminhoPai to set
	 */
	public void setCaminhoPai(String caminhoPai) {
		this.caminhoPai = caminhoPai;
	}

	public String getCaminhoOriginal() {
		return caminhoOriginal;
	}

	public void setCaminhoOriginal(String caminhoOriginal) {
		this.caminhoOriginal = caminhoOriginal;
	}

	/* (non-Javadoc)
	 * @see br.com.hfsfolder.model.PreFile#limparDados()
	 */
	@Override
	public void limparDados() {
		super.limparDados();
		this.codigo = 0;
		this.ordem = 0;
		this.codDirPai = 0;
		this.tipo = 'A';
		this.caminho = "";
		this.nomePai = "";
		this.caminhoPai = "";
		this.caminhoOriginal = "";
	}

	@Override
	public String toString() {
		return "Folder [codigo=" + codigo + ", ordem=" + ordem + ", codDirPai=" + codDirPai + ", tipo=" + tipo
				+ ", caminho=" + caminho + ", nomePai=" + nomePai + ", caminhoPai=" + caminhoPai + "]";
	}

	public String toInsert(int naba) {		
		return "INSERT INTO Diretorios(aba, cod, ordem, nome, tam, tipo, modificado, atributos, coddirpai, caminho) VALUES("+naba+","+
		codigo + "," + ordem + ",'" + getNome() + "'," + getTamanho() + ",'" + tipo + "','" + getModificadoFormatado()  + "','" 
				+ getAtributos()  + "'," + codDirPai + ",'"   + getCaminho() + "');"; //,'" + nomePai + "','" + caminhoPai;
	}
	
	public String toCVS() {
		return super.toCVS() + ";" + codigo + ";" + ordem + ";" + codDirPai + ";" + tipo + ";" + getCaminho(); // + ";" + nomePai + ";" + caminhoPai;
	}	
}
