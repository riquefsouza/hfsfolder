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
	private String name;

	/** The tamanho. */
	private long size;

	/** The modificado. */
	private Calendar modified;

	/** The atributos. */
	private String attributes;

	/** The tamanho formatado. */
	private String formatedSize;

	/** The modificado formatado. */
	private String formatedModified;

	/**
	 * Instantiates a new pre file.
	 */
	public PreFile() {
		super();
	}

	/**
	 * Instantiates a new pre file.
	 *
	 * @param name the name
	 * @param size the size
	 * @param modified the modified
	 * @param attributes the attributes
	 * @param formatSize the format size
	 * @param formatModified the format modified
	 */
	public PreFile(String name, long size, Calendar modified, String attributes, String formatSize,
			String formatModified) {
		super();
		this.name = name;
		this.size = size;
		this.modified = modified;
		this.attributes = attributes;
		this.formatedSize = formatSize;
		this.formatedModified = formatModified;
	}

	/**
	 * Gets the name.
	 *
	 * @return the name
	 */
	public String getName() {
		return name;
	}

	/**
	 * Sets the name.
	 *
	 * @param name the new name
	 */
	public void setName(String name) {
		this.name = name;
	}

	/**
	 * Gets the size.
	 *
	 * @return the size
	 */
	public long getSize() {
		return size;
	}

	/**
	 * Sets the size.
	 *
	 * @param size the new size
	 */
	public void setSize(long size) {
		this.size = size;
	}

	/**
	 * Gets the modified.
	 *
	 * @return the modified
	 */
	public Calendar getModified() {
		return modified;
	}

	/**
	 * Sets the modified.
	 *
	 * @param modified the new modified
	 */
	public void setModified(Calendar modified) {
		this.modified = modified;
	}

	/**
	 * Gets the attributes.
	 *
	 * @return the attributes
	 */
	public String getAttributes() {
		return attributes;
	}

	/**
	 * Sets the attributes.
	 *
	 * @param attributes the new attributes
	 */
	public void setAttributes(String attributes) {
		this.attributes = attributes;
	}

	/**
	 * Gets the format size.
	 *
	 * @return the format size
	 */
	public String getFormatedSize() {
		return formatedSize;
	}

	/**
	 * Sets the format size.
	 *
	 * @param formatSize the new format size
	 */
	public void setFormatedSize(String formatedSize) {
		this.formatedSize = formatedSize;
	}

	/**
	 * Gets the format modified.
	 *
	 * @return the format modified
	 */
	public String getFormatedModified() {
		return formatedModified;
	}

	/**
	 * Sets the format modified.
	 *
	 * @param formatModified the new format modified
	 */
	public void setFormatedModified(String formatedModified) {
		this.formatedModified = formatedModified;
	}

	/**
	 * Limpar dados.
	 */
	public void limparDados() {
		this.name = "";
		this.size = 0;
		this.modified = Calendar.getInstance();
		this.attributes = "";
		this.formatedSize = "";
		this.formatedModified = "";
	}

	@Override
	public String toString() {
		return "PreFile [name=" + name + ", size=" + size + ", modified=" + modified + ", attributes=" + attributes
				+ ", formatSize=" + formatedSize + ", formatModified=" + formatedModified + "]";
	}

	/**
	 * To insert.
	 *
	 * @return the string
	 */
	public String toInsert() {
		return "'" + getName() + "'," + size + ",'" + formatedModified + "','" + attributes + "'";
	}

	/**
	 * To CVS.
	 *
	 * @return the string
	 */
	public String toCVS() {
		return getName() + ";" + size + ";" + formatedModified + ";" + attributes;
	}
}
