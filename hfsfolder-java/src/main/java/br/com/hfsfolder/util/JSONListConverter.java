/**
 * @author Henrique Figueiredo de Souza
 * @version 1.0
 * @since 2019
 */
package br.com.hfsfolder.util;

import java.io.IOException;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;

/**
 * The Class JSONListConverter1.
 *
 * @param <T>
 *            the generic type
 */
public final class JSONListConverter<T> implements Serializable {

	/** The Constant serialVersionUID. */
	private static final long serialVersionUID = 1L;

	/** The log. */
	private static Logger log = LogManager.getLogger(JSONListConverter.class);

	/**
	 * Lista to JSON.
	 *
	 * @param lista
	 *            the lista
	 * @return the string
	 */
	public String listaToJSON(List<T> lista) {
		try {
			ObjectMapper objectMapper = new ObjectMapper();
			objectMapper.enable(SerializationFeature.INDENT_OUTPUT);

			return objectMapper.writeValueAsString(lista);

		} catch (JsonProcessingException e) {
			log.fatal(e.getMessage());
		}
		return "";
	}

	/**
	 * Json to lista.
	 *
	 * @param textoJSON
	 *            the texto JSON
	 * @param mapType
	 *            the map type
	 * @return the list
	 */
	public List<T> jsonToLista(String textoJSON, TypeReference<List<T>> mapType) {
		try {
			ObjectMapper objectMapper = new ObjectMapper();
			//objectMapper.enable(SerializationFeature.INDENT_OUTPUT);

			//TypeReference<List<T>> mapType = new TypeReference<List<T>>() {
			//};
			List<T> jsonToList = objectMapper.readValue(textoJSON, mapType);
			return jsonToList;			
		} catch (IOException e) {
			log.fatal(e.getMessage());
		}
		return new ArrayList<T>();
	}

}
