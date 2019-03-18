/**
 * @author Henrique Figueiredo de Souza
 * @version 1.0
 * @since 2019
 */
package br.com.hfsfolder.util;

import java.io.BufferedReader;
import java.io.InputStreamReader;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

/**
 * The Class Reading.
 */
public final class Reading {

	/** The log. */
	private static Logger log = LogManager.getLogger(Reading.class);

	/**
	 * Read int.
	 *
	 * @return the int
	 */
	public static int readInt() {
		BufferedReader brentrada = new BufferedReader(new InputStreamReader(System.in));
		String sret = new String();
		int nret = 0;
		try {
			sret = brentrada.readLine();
			nret = Integer.parseInt(sret);
		} catch (Exception e) {
			log.error(e);
		}
		return nret;
	}
}
