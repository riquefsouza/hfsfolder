/**
 * @author Henrique Figueiredo de Souza
 * @version 1.0
 * @since 2019
 */
package br.com.hfsfolder;

import java.io.File;
import java.io.IOException;
import java.math.BigDecimal;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;
import java.util.Optional;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import br.com.hfsfolder.model.Folder;
import br.com.hfsfolder.model.FolderOrder;
import br.com.hfsfolder.model.PreFile;
import br.com.hfsfolder.util.JSONListConverter;
import br.com.hfsfolder.util.VisitFoldersUtil;

/**
 * The Class ProcessFolders.
 */
public class ProcessFolders {
	
	/** The log. */
	private static Logger log = LogManager.getLogger(ProcessFolders.class);

	/**
	 * Format double.
	 *
	 * @param formato the formato
	 * @param valor the valor
	 * @return the string
	 */
	private static String FormatDouble(String formato, double valor) {
		DecimalFormat fmt = new DecimalFormat(formato);
		return fmt.format(valor);
	}

	/**
	 * Monta tamanho big.
	 *
	 * @param nTam the n tam
	 * @return the string
	 */
	private static String MountBigSize(BigDecimal nTam) {
		BigDecimal nUmKilo, nUmMega, nUmGiga, nUmTera, nUmPeta;

		nUmKilo = new BigDecimal(1024);
		nUmMega = nUmKilo.multiply(nUmKilo);
		nUmGiga = nUmMega.multiply(nUmKilo);
		nUmTera = nUmGiga.multiply(nUmKilo);
		nUmPeta = nUmTera.multiply(nUmKilo);

		if (nTam.compareTo(nUmKilo) == -1) {
			return FormatDouble("#,##0.00", nTam.doubleValue()) + " Byte(s)";
		} else if (nTam.compareTo(nUmKilo) == 1 && nTam.compareTo(nUmMega) == -1) {
			nTam = nTam.divide(nUmKilo);
			return FormatDouble("#,##0.00", nTam.doubleValue()) + " KByte(s)";
		} else if (nTam.compareTo(nUmMega) == 1 && nTam.compareTo(nUmGiga) == -1) {
			nTam = nTam.divide(nUmMega);
			return FormatDouble("#,##0.00", nTam.doubleValue()) + " MByte(s)";
		} else if (nTam.compareTo(nUmGiga) == 1 && nTam.compareTo(nUmTera) == -1) {
			nTam = nTam.divide(nUmGiga);
			return FormatDouble("#,##0.00", nTam.doubleValue()) + " GByte(s)";
		} else if (nTam.compareTo(nUmTera) == 1 && nTam.compareTo(nUmPeta) == -1) {
			nTam = nTam.divide(nUmTera);
			return FormatDouble("#,##0.00", nTam.doubleValue()) + " TByte(s)";
		} else {
			nTam = nTam.divide(nUmPeta);
			return FormatDouble("#,##0.00", nTam.doubleValue()) + " PByte(s)";
		}
	}

	/**
	 * Arquivo atributos.
	 *
	 * @param arquivo the arquivo
	 * @return the string
	 */
	private static String prefileAttributos(File arquivo) {
		String sAtributos = "";

		if (arquivo != null) {
			if (!arquivo.canWrite()) {
				sAtributos += "[ROL]";
			}
			if (arquivo.isHidden()) {
				sAtributos += "[HID]";
			}
			if (arquivo.isDirectory()) {
				sAtributos += "[DIR]";
			}
			if (arquivo.isFile()) {
				sAtributos += "[ARQ]";
			}
		}
		return sAtributos;
	}

	/**
	 * Atributes to arquivo.
	 *
	 * @param file the file
	 * @return the pre file
	 */
	private static PreFile attributesToPreFile(File file) {
		Calendar cal = Calendar.getInstance();
		cal.setTimeInMillis(file.lastModified());

		PreFile arquivo = new PreFile();
		arquivo.setName(file.getName().replaceAll("'", "''"));
		arquivo.setSize(file.length());
		arquivo.setModified(cal);
		arquivo.setAttributes(prefileAttributos(file));
		arquivo.setFormatedSize(MountBigSize(new BigDecimal(arquivo.getSize())));
		
		SimpleDateFormat fmt = new SimpleDateFormat("dd/MM/yyyy hh:mm:ss");
		arquivo.setFormatedModified(fmt.format(arquivo.getModified().getTime()));
		return arquivo;
	}

	/**
	 * Creates the folder.
	 *
	 * @param dirBefore the dir before
	 * @param file the file
	 * @param folderOrder the folder order
	 * @return the optional
	 */
	private static Optional<Folder> createFolder(File file, FolderOrder folderOrder) {
		PreFile arquivo = attributesToPreFile(file);
		Folder dir = new Folder(arquivo);

		if (file.isDirectory()) {
			dir.setFolderType('D');
		} else {						
			dir.setFolderType('A');			
		}
		
		String sPath = file.getAbsolutePath();
		
		Pattern pattern = Pattern.compile("[a-zA-Z]:\\\\");
		Matcher matcher = pattern.matcher(sPath);
		if (matcher.find()) {
			sPath = sPath.substring(3);	
		}
		
		if (sPath.startsWith("/")) {
			sPath = sPath.substring(1);
		}
		
		dir.setPath(sPath.replaceAll("'", "''").replaceAll("\\\\", "/"));
		dir.setOriginalPath(file.getAbsolutePath());

		if (!dir.getPath().contains("/")) {
			folderOrder.setCodFolder(folderOrder.getCodFolder()+1);
			folderOrder.setOrder(1);
		} else {
			folderOrder.setOrder(folderOrder.getOrder()+1);	
		}

		dir.setCode(folderOrder.getCodFolder());
		dir.setOrder(folderOrder.getOrder());

		
		return Optional.of(dir);
	}
	
	/**
	 * Process.
	 *
	 * @param folder the folder
	 * @return the list
	 */
	private static List<Folder> process(String folder) {
		List<Folder> listaFolders = new ArrayList<Folder>();
		Optional<Folder> dir = Optional.empty();
		FolderOrder folderOrder = new FolderOrder(-1, 0);

		log.info("Processing folders!");
		
		List<Path> listaPaths = VisitFoldersUtil.getPathsFromFiles(folder)
				.collect(Collectors.toList());
		
		for (Path path : listaPaths) {			
			dir = ProcessFolders.createFolder(path.toFile(), folderOrder);
			if (dir.isPresent()) {
				listaFolders.add(dir.get());
			}
		}
		
		for (Folder item : listaFolders) {
			
			String pathChild = item.getOriginalPath().substring(0, 
					item.getOriginalPath().lastIndexOf(File.separatorChar));
			
			Optional<Folder> pathFather = listaFolders.stream()
				.filter(f -> f.getOriginalPath().equals(pathChild))
				.findFirst();
			
			if (pathFather.isPresent()) {
				item.setParentCodFolder(pathFather.get().getOrder());
				item.setParentName(pathFather.get().getName());
				item.setParentPath(pathFather.get().getPath());
			}
		}
		
		listaFolders = listaFolders.stream()
				.sorted((s1, s2) -> s1.getPath().compareTo(s2.getPath()))
				.collect(Collectors.toList());
		
		return listaFolders;
	}
	
	/**
	 * Process folders to json.
	 *
	 * @param folder the folder
	 * @return the string
	 */
	public static String processFoldersToJson(String folder) {
		JSONListConverter<Folder> jsonFolders = new JSONListConverter<Folder>();
		List<Folder> lista = process(folder);
		
		return jsonFolders.listaToJSON(lista);
	}
	
	public static void processFoldersToFile(String data, String file) {
		try {
			Files.write(Paths.get(file), data.getBytes());
		} catch (IOException e) {
			log.error(e);
		}
	}
	
	public static String processFoldersToInsert(String folder, int naba) {
		List<Folder> lista = process(folder);
		String result = "";
		
		for (Folder item : lista) {
			result += item.toInsert(naba)+"\n";
		}

		return result;
	}
	
	public static String processFoldersToCSV(String folder) {
		List<Folder> lista = process(folder);
		String result = "Code;Order;Name;Size;\"Folder Type\";\"Formated Modified\";Attributes;\"Parent Code Folder\";Path\n";
		
		for (Folder item : lista) {
			result += item.toCVS()+"\n";
		}

		return result;
	}
}
