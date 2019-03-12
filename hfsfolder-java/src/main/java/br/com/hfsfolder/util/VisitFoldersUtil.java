/**
 * @author Henrique Figueiredo de Souza
 * @version 1.0
 * @since 2019
 */
package br.com.hfsfolder.util;

import java.io.IOException;
import java.io.UncheckedIOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

/**
 * The Class VisitFoldersUtil.
 */
public final class VisitFoldersUtil {

	/** The log. */
	private static Logger log = LogManager.getLogger(VisitFoldersUtil.class);

	/**
	 * Lines.
	 *
	 * @param p the p
	 * @return the stream
	 */
	private static Stream<String> lines(Path p) {
		try {
			return Files.lines(p);
		} catch (IOException e) {
			log.error(e);
			throw new UncheckedIOException(e);
		}
	}

	/**
	 * Gets the list from files.
	 *
	 * @param folder the folder
	 * @return the list from files
	 */
	public static List<String> getListFromFiles(String folder) {
		List<String> lista = new ArrayList<String>();
		Path start = Paths.get(folder);
		try (Stream<Path> stream = Files.walk(start, Integer.MAX_VALUE)) {
			lista = stream.map(String::valueOf).sorted().collect(Collectors.toList());
		} catch (IOException e) {
			log.error(e);
			// throw new IOException(e);
		}
		return lista;
	}

	/**
	 * Gets the paths from files.
	 *
	 * @param folder the folder
	 * @return the paths from files
	 */
	public static Stream<Path> getPathsFromFiles(String folder) {
		return getListFromFiles(folder)
				.stream()
				.map(item -> Paths.get(item));
	}
	
	/**
	 * Gets the paths from files.
	 *
	 * @param folder the folder
	 * @param fileSufix the file sufix
	 * @return the paths from files
	 */
	public static Stream<Path> getPathsFromFiles(String folder, String fileSufix) {
		return getPathsFromFiles(folder)
				.filter(p -> p.toString().endsWith(fileSufix));
	}	 

	/**
	 * Gets the all lines from files.
	 *
	 * @param folder the folder
	 * @param fileSufix the file sufix
	 * @return the all lines from files
	 */
	public static Stream<String> getAllLinesFromFiles(String folder, String fileSufix) {
		return getPathsFromFiles(folder, fileSufix)
				.flatMap(p -> lines(p));
	}

	/**
	 * Gets the all chars from files.
	 *
	 * @param folder the folder
	 * @param fileSufix the file sufix
	 * @return the all chars from files
	 */
	public static IntStream getAllCharsFromFiles(String folder, String fileSufix) {
		return getPathsFromFiles(folder, fileSufix)
				.flatMap(p -> lines(p))
				.flatMapToInt((String s) -> s.chars());
	}
}
