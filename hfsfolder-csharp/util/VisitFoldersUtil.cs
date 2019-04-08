/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 08/04/2019
 * Time: 14:09
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.IO;
using System.Collections.Generic;
using hfsfolder.model;

namespace hfsfolder.util
{
	/// <summary>
	/// Description of VisitFoldersUtil.
	/// </summary>
	public class VisitFoldersUtil
	{			
		public static List<PreFile> getListFromFiles(String folder) {
			List<PreFile> lst = new List<PreFile>();			
			DirectoryInfo dir = new DirectoryInfo(folder);
			lst.Add(attributesToPreFile(dir));
			TraverseDirs(lst, dir);
			return lst;
		}
		
		private static string FormatDecimal(decimal valor) {
	        return valor.ToString("#,##0.00");
		}
		
		private static string MountBigSize(decimal nTam) {
			decimal nUmKilo, nUmMega, nUmGiga, nUmTera, nUmPeta;
			decimal nTamLocal;

			nUmKilo = 1024;
			nUmMega = nUmKilo * 1024;
			nUmGiga = nUmMega * 1024;
			nUmTera = nUmGiga * 1024;
			nUmPeta = nUmTera * 1024;

			if (nTam.CompareTo(nUmKilo) == -1) {
				nTamLocal = nTam;
				return FormatDecimal(nTamLocal) + " Byte(s)";
			} else if (nTam.CompareTo(nUmKilo) == 1 && nTam.CompareTo(nUmMega) == -1) {
				nTamLocal = nTam / nUmKilo;
				return FormatDecimal(nTamLocal) + " KByte(s)";
			} else if (nTam.CompareTo(nUmMega) == 1 && nTam.CompareTo(nUmGiga) == -1) {
				nTamLocal = nTam / nUmMega;
				return FormatDecimal(nTamLocal) + " MByte(s)";
			} else if (nTam.CompareTo(nUmGiga) == 1 && nTam.CompareTo(nUmTera) == -1) {
				nTamLocal = nTam / nUmGiga;
				return FormatDecimal(nTamLocal) + " GByte(s)";
			} else if (nTam.CompareTo(nUmTera) == 1 && nTam.CompareTo(nUmPeta) == -1) {
				nTamLocal = nTam / nUmTera;
				return FormatDecimal(nTamLocal) + " TByte(s)";
			} else {
				nTamLocal = nTam / nUmPeta;
				return FormatDecimal(nTamLocal) + " PByte(s)";
			}
		}
		
		private static PreFile attributesToPreFile(DirectoryInfo dir) {
			PreFile pf = new PreFile();
			string sAtributos = "";
			string sName = dir.Name.Replace("'", "''");
			pf.setName(sName);
			pf.setSize(0);
			pf.setModified(dir.LastWriteTime);

			sAtributos += "[DIR]";
			
			if (dir.Attributes==FileAttributes.Hidden) {
				sAtributos += "[HID]";
			}
			if (dir.Attributes==FileAttributes.System) {
				sAtributos += "[SYS]";
			} 			
			
			pf.setAttributes(sAtributos);
			pf.setOriginalPath(dir.FullName);
			pf.setDirectory(true);
			pf.setFormatedSize(MountBigSize(pf.getSize()));		
			pf.setFormatedModified(pf.getModified().ToString("dd/MM/yyyy hh:mm:ss"));
			
			return pf;
		}

		private static PreFile attributesToPreFile(FileInfo file) {
			PreFile pf = new PreFile();
			string sAtributos = "";
			string sName = file.Name.Replace("'", "''");
			pf.setName(sName);
			pf.setSize(file.Length);
			pf.setModified(file.LastWriteTime);

			sAtributos += "[ARQ]";
			
			if (file.IsReadOnly) {
				sAtributos += "[ROL]";
			}
			if (file.Attributes==FileAttributes.Hidden) {
				sAtributos += "[HID]";
			}
			if (file.Attributes==FileAttributes.System) {
				sAtributos += "[SYS]";
			} 			
			
			pf.setAttributes(sAtributos);
			pf.setOriginalPath(file.FullName);
			pf.setDirectory(false);
			pf.setFormatedSize(MountBigSize(pf.getSize()));		
			pf.setFormatedModified(pf.getModified().ToString("dd/MM/yyyy hh:mm:ss"));
			
			return pf;
		}
		
		private static void TraverseDirs(List<PreFile> lst, DirectoryInfo dir)
		{
			try
			{
				foreach (DirectoryInfo iInfo in dir.GetDirectories())
				{
					//if (iInfo.Name.EndsWith(fileSufix)){
						lst.Add(attributesToPreFile(iInfo));
					//}
					TraverseDirs(lst, iInfo);
				}
			}
			catch (Exception)
			{				
			}
			
			try
			{
				foreach (FileInfo iInfo in dir.GetFiles())
				{
					//if (iInfo.Name.EndsWith(fileSufix)){
						lst.Add(attributesToPreFile(iInfo));
					//}
				}
			}
			catch (Exception)
			{
			}
		}		
	}
}
