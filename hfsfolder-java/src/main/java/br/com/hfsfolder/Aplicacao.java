/**
 * @author Henrique Figueiredo de Souza
 * @version 1.0
 * @since 2019
 */
package br.com.hfsfolder;

import java.io.IOException;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import br.com.hfsfolder.util.Leitura;

/**
 * The Class Aplicacao.
 */
public class Aplicacao {

	/** The log. */
	private static Logger log = LogManager.getLogger(Aplicacao.class);

	/**
	 * The main method.
	 *
	 * @param args the arguments
	 * @throws IOException Signals that an I/O exception has occurred.
	 */
	public static void main(String[] args) throws IOException {
		String folder = "";
		boolean tojson = false, tofile = false, toinsert = false, tocvs = false;
		
		if (args.length > 0) {
			
			for (String opt : args) {
				if (!opt.contains("--")) {
					folder = opt;
				}
				if (opt.contains("--version")) {
					System.out.println("hfsfolder-to-json 1.0");
				}
				if (opt.contains("--tojson")) {
					tojson = true;
				}	
				if (opt.contains("--tofile")) {
					tofile = true;
				}				
				if (opt.contains("--toinsert")) {
					toinsert = true;
				}				
				if (opt.contains("--tocvs")) {
					tocvs = true;
				}	
			}
			
			if (!folder.isEmpty()) {
				log.info("Processing folders!");
				String data = "";
				if (tojson) {
					data = ProcessFolders.processFoldersToJson(folder);
					System.out.println(data);
				} if (toinsert) {
					System.out.print("Inform tab number: ");
					int naba = Leitura.LerInt();
					data = ProcessFolders.processFoldersToInsert(folder, naba);
					System.out.println(data);
				} if (tocvs) {	
					data = ProcessFolders.processFoldersToCVS(folder);
					System.out.println(data);					
				}
				
				if (tofile && !data.isEmpty()) {
					ProcessFolders.processFoldersToFile(data, "hfsfolder.json");
				}
			}
		} else {
			System.out.println(
			"HFSFolder to JSON (java 11 only)\n"+
			"Usage:\n"+
			"    java -jar hfsfolder-to-json.jar /folder\n\n"+
			"Options:\n"+
			"    --version\n"+
			"    --tojson\n"+
			"    --toinsert\n"+
			"    --tocvs\n"+
			"    --tofile\n\n"+
			"Example:\n"+
			"    java -jar hfsfolder-to-json.jar /folder --tojson --tofile --version\n");
		}
	}

}
