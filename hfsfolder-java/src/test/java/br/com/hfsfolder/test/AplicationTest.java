/**
 * @author Henrique Figueiredo de Souza
 * @version 1.0
 * @since 2019
 */
package br.com.hfsfolder.test;

import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;

import br.com.hfsfolder.ProcessFolders;

/**
 * The Class AplicationTest.
 */
public class AplicationTest {

	/**
	 * Exist result.
	 */
	@Test
	public void existResult() {
		String json = ProcessFolders.processFoldersToJson("C:/RetroArch");
		assertTrue(json.length() > 0);
	}
}
