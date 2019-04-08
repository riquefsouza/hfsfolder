/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 08/04/2019
 * Time: 14:52
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Collections.Generic;
using hfsfolder.model;
using hfsfolder.util;

namespace hfsfolder
{
	/// <summary>
	/// Description of ProcessFolders.
	/// </summary>
	public class ProcessFolders
	{		
		
		private static Folder createFolder(PreFile pf, FolderOrder folderOrder) {
			Folder folder = new Folder(pf);
	
			if (pf.isDirectory()) {
				folder.setFolderType('D');
			} else {						
				folder.setFolderType('A');			
			}
			
			string sPath = pf.getOriginalPath();
			
			if (Regex.IsMatch(sPath, "[a-zA-Z]:\\\\")) {
				sPath = sPath.Substring(3);
				folder.separatorChar = '\\';
			}

			if (Regex.IsMatch(sPath, "[a-zA-Z]:/")) {
				sPath = sPath.Substring(3);
				folder.separatorChar = '/';
			}
			
			if (sPath.StartsWith("/")) {
				sPath = sPath.Substring(1);
				folder.separatorChar = '/';
			}
			
			folder.setPath(sPath.Replace("'", "''").Replace("\\", "/"));
			folder.setOriginalPath(pf.getOriginalPath());
	
			if (!folder.getPath().Contains("/")) {
				folderOrder.setCodFolder(folderOrder.getCodFolder()+1);
				folderOrder.setOrder(1);
			} else {
				folderOrder.setOrder(folderOrder.getOrder()+1);	
			}
	
			folder.setCode(folderOrder.getCodFolder());
			folder.setOrder(folderOrder.getOrder());
				
			return folder;
		}
				
		private static List<Folder> process(string folder) {
			List<Folder> listaFolders = new List<Folder>();
			Folder dir;
			FolderOrder folderOrder = new FolderOrder(-1, 0);
	
			Console.WriteLine("Processing folders!");
			
			List<PreFile> listaPrefiles = VisitFoldersUtil.getListFromFiles(folder);
			
			foreach (PreFile pf in listaPrefiles) {
				dir = ProcessFolders.createFolder(pf, folderOrder);
				listaFolders.Add(dir);
			}
			
			foreach (Folder item in listaFolders) {
				
				string pathChild = item.getOriginalPath().Substring(0, 
						item.getOriginalPath().LastIndexOf(item.separatorChar));
				
				Folder pathFather = listaFolders.Find(f => f.getOriginalPath().Equals(pathChild));
				
				if (pathFather!=null) {
					item.setParentCodFolder(pathFather.getOrder());
					item.setParentName(pathFather.getName());
					item.setParentPath(pathFather.getPath());
				}
			}
			
			listaFolders.Sort();
			
			return listaFolders;
		}		
		
		public static string processFoldersToJson(string folder) {			
			List<Folder> lista = process(folder);
			Folder item;
			string result = "[ ";
	
			for (int i = 0; i < lista.Count; i++) {
				item = lista[i];
	
				if (i == 0)
					result += item.ToJSON();
				else
					result += ", " + item.ToJSON();
			}
	
			return result + " ]";

		}
		
		public static void processFoldersToFile(string data, string sfile) {
			FileStream fileStream = null;            
			try {        
				fileStream = new FileStream(sfile, 
					FileMode.OpenOrCreate, FileAccess.Write);
				fileStream.Write(Encoding.Default.GetBytes(data), 0, data.Length);
				fileStream.Flush();
			} catch (FileNotFoundException ioEx) {	            
				Console.WriteLine(ioEx.Message);				
			} finally {
				if(fileStream != null){
					fileStream.Close();
				}
			} 
		}
		
		public static String processFoldersToInsert(string folder, int naba) {
			List<Folder> lista = process(folder);
			string result = "";
			
			foreach (Folder item in lista) {
				result += item.ToInsert(naba)+"\n";
			}
	
			return result;
		}
		
		public static string processFoldersToCSV(string folder) {
			List<Folder> lista = process(folder);
			string result = "Code;Order;Name;Size;\"Folder Type\";\"Formated Modified\";Attributes;\"Parent Code Folder\";Path\n";
			
			foreach (Folder item in lista) {
				result += item.ToCVS()+"\n";
			}
	
			return result;
		}
		
		
	}
}
