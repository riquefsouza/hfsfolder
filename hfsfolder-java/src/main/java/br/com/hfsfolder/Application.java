/**
 * @author Henrique Figueiredo de Souza
 * @version 1.0
 * @since 2019
 */
package br.com.hfsfolder;

import java.io.IOException;

import br.com.hfsfolder.util.Reading;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

/**
 * The Class Application.
 */
public class Application {

	private static Logger log = LogManager.getLogger(Application.class);

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
					System.out.println("hfsfolder 1.0");
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
				String data = "", outFile = "hfsfolder";
				if (tojson) {
					outFile += ".json";
					data = ProcessFolders.processFoldersToJson(folder);
				}
				if (toinsert) {
					System.out.print("Inform tab number: ");
					int naba = Reading.readInt();
					outFile += "-insert.sql";
					data = ProcessFolders.processFoldersToInsert(folder, naba);
				}
				if (tocvs) {
					outFile += ".csv";
					data = ProcessFolders.processFoldersToCSV(folder);
				}

				if (tofile && !data.isEmpty()) {
					ProcessFolders.processFoldersToFile(data, outFile);
					log.info("Finish process folders!");
				} else if (!data.isEmpty()) {
					System.out.println(data);
				}
				
				if (!tojson && !toinsert && !tocvs && !tofile) {
					log.info("Inform option!");
				}
			} else {
				if (tojson || toinsert || tocvs || tofile) {
					log.info("Inform folder!");
				}
			}
		} else {
			System.out.println("HFSFolder (java 11 only)\n"
					+ "Usage:\n" 
					+ "    java -jar hfsfolder-java.jar /folder\n\n"
					+ "Options:\n"
					+ "    --version\n"
					+ "    --tojson\n"
					+ "    --toinsert\n" 
					+ "    --tocvs\n" 
					+ "    --tofile\n\n" 
					+ "Example:\n"
					+ "    java -jar hfsfolder-java.jar /folder --tojson --tofile --version\n");
		}
	}

}
