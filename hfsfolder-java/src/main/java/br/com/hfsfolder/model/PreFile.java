/**
 * @author Henrique Figueiredo de Souza
 * @version 1.0
 * @since 2019
 */
package br.com.hfsfolder.model;

import java.util.Calendar;

/**
 * The Class PreFile.
 */
public class PreFile {

	/** The nome. */
	private String nome;
	
	/** The tamanho. */
	private long tamanho;
	
	/** The modificado. */
	private Calendar modificado;
	
	/** The atributos. */
	private String atributos;
	
	/** The tamanho formatado. */
	private String tamanhoFormatado;
	
	/** The modificado formatado. */
	private String modificadoFormatado;

	/**
	 * Instantiates a new pre file.
	 */
	public PreFile() {
		super();
	}

	/**
	 * Instantiates a new pre file.
	 *
	 * @param nome the nome
	 * @param tamanho the tamanho
	 * @param modificado the modificado
	 * @param atributos the atributos
	 * @param tamanhoFormatado the tamanho formatado
	 * @param modificadoFormatado the modificado formatado
	 */
	public PreFile(String nome, long tamanho, Calendar modificado, String atributos, String tamanhoFormatado,
			String modificadoFormatado) {
		super();
		this.nome = nome;
		this.tamanho = tamanho;
		this.modificado = modificado;
		this.atributos = atributos;
		this.tamanhoFormatado = tamanhoFormatado;
		this.modificadoFormatado = modificadoFormatado;
	}

	/**
	 * Gets the nome.
	 *
	 * @return the nome
	 */
	public String getNome() {
		return nome;
	}

	/**
	 * Sets the nome.
	 *
	 * @param nome the new nome
	 */
	public void setNome(String nome) {
		this.nome = nome;
	}

	/**
	 * Gets the tamanho.
	 *
	 * @return the tamanho
	 */
	public long getTamanho() {
		return tamanho;
	}

	/**
	 * Sets the tamanho.
	 *
	 * @param tamanho the new tamanho
	 */
	public void setTamanho(long tamanho) {
		this.tamanho = tamanho;
	}

	/**
	 * Gets the modificado.
	 *
	 * @return the modificado
	 */
	public Calendar getModificado() {
		return modificado;
	}

	/**
	 * Sets the modificado.
	 *
	 * @param modificado the new modificado
	 */
	public void setModificado(Calendar modificado) {
		this.modificado = modificado;
	}

	/**
	 * Gets the atributos.
	 *
	 * @return the atributos
	 */
	public String getAtributos() {
		return atributos;
	}

	/**
	 * Sets the atributos.
	 *
	 * @param atributos the new atributos
	 */
	public void setAtributos(String atributos) {
		this.atributos = atributos;
	}

	/**
	 * Gets the tamanho formatado.
	 *
	 * @return the tamanho formatado
	 */
	public String getTamanhoFormatado() {
		return tamanhoFormatado;
	}

	/**
	 * Sets the tamanho formatado.
	 *
	 * @param tamanhoFormatado the new tamanho formatado
	 */
	public void setTamanhoFormatado(String tamanhoFormatado) {
		this.tamanhoFormatado = tamanhoFormatado;
	}

	/**
	 * Gets the modificado formatado.
	 *
	 * @return the modificado formatado
	 */
	public String getModificadoFormatado() {
		return modificadoFormatado;
	}

	/**
	 * Sets the modificado formatado.
	 *
	 * @param modificadoFormatado the new modificado formatado
	 */
	public void setModificadoFormatado(String modificadoFormatado) {
		this.modificadoFormatado = modificadoFormatado;
	}

	/**
	 * Limpar dados.
	 */
	public void limparDados() {
		this.nome = "";
		this.tamanho = 0;
		this.modificado = Calendar.getInstance();
		this.atributos = "";
		this.tamanhoFormatado = "";
		this.modificadoFormatado = "";
	}

	@Override
	public String toString() {
		return "PreFile [nome=" + nome + ", tamanho=" + tamanho + ", modificado=" + modificado + ", atributos="
				+ atributos + ", tamanhoFormatado=" + tamanhoFormatado + ", modificadoFormatado=" + modificadoFormatado
				+ "]";
	}

	public String toInsert() {
		return "'" + getNome() + "'," + tamanho + ",'" + modificadoFormatado  + "','" + atributos  + "'";		
	}
	
	public String toCVS() {
		return getNome() + ";" + tamanho + ";" + modificadoFormatado  + ";" + atributos;		
	}	
}
