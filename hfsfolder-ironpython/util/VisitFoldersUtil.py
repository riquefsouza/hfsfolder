# 
# * Created by SharpDevelop.
# * User: henrique.souza
# * Date: 08/04/2019
# * Time: 14:09
# *
# * To change this template use Tools | Options | Coding | Edit Standard Headers.
# 
from System import *
from System.IO import *
from System.Collections.Generic import *
from hfsfolder.model import *

class VisitFoldersUtil(object):
	""" <summary>
	 Description of VisitFoldersUtil.
	 </summary>
	"""
	def getListFromFiles(folder):
		lst = List[PreFile]()
		dir = DirectoryInfo(folder)
		lst.Add(VisitFoldersUtil.attributesToPreFile(dir))
		VisitFoldersUtil.TraverseDirs(lst, dir)
		return lst

	getListFromFiles = staticmethod(getListFromFiles)

	def FormatDecimal(valor):
		return valor.ToString("#,##0.00")

	FormatDecimal = staticmethod(FormatDecimal)

	def MountBigSize(nTam):
		nUmKilo = 1024
		nUmMega = nUmKilo * 1024
		nUmGiga = nUmMega * 1024
		nUmTera = nUmGiga * 1024
		nUmPeta = nUmTera * 1024
		if nTam.CompareTo(nUmKilo) == -1:
			nTamLocal = nTam
			return VisitFoldersUtil.FormatDecimal(nTamLocal) + " Byte(s)"
		elif nTam.CompareTo(nUmKilo) == 1 and nTam.CompareTo(nUmMega) == -1:
			nTamLocal = nTam / nUmKilo
			return VisitFoldersUtil.FormatDecimal(nTamLocal) + " KByte(s)"
		elif nTam.CompareTo(nUmMega) == 1 and nTam.CompareTo(nUmGiga) == -1:
			nTamLocal = nTam / nUmMega
			return VisitFoldersUtil.FormatDecimal(nTamLocal) + " MByte(s)"
		elif nTam.CompareTo(nUmGiga) == 1 and nTam.CompareTo(nUmTera) == -1:
			nTamLocal = nTam / nUmGiga
			return VisitFoldersUtil.FormatDecimal(nTamLocal) + " GByte(s)"
		elif nTam.CompareTo(nUmTera) == 1 and nTam.CompareTo(nUmPeta) == -1:
			nTamLocal = nTam / nUmTera
			return VisitFoldersUtil.FormatDecimal(nTamLocal) + " TByte(s)"
		else:
			nTamLocal = nTam / nUmPeta
			return VisitFoldersUtil.FormatDecimal(nTamLocal) + " PByte(s)"

	MountBigSize = staticmethod(MountBigSize)

	def attributesToPreFile(dir):
		pf = PreFile()
		sAtributos = ""
		sName = dir.Name.Replace("'", "''")
		pf.setName(sName)
		pf.setSize(0)
		pf.setModified(dir.LastWriteTime)
		sAtributos += "[DIR]"
		if dir.Attributes == FileAttributes.Hidden:
			sAtributos += "[HID]"
		if dir.Attributes == FileAttributes.System:
			sAtributos += "[SYS]"
		pf.setAttributes(sAtributos)
		pf.setOriginalPath(dir.FullName)
		pf.setDirectory(True)
		pf.setFormatedSize(VisitFoldersUtil.MountBigSize(pf.getSize()))
		pf.setFormatedModified(pf.getModified().ToString("dd/MM/yyyy hh:mm:ss"))
		return pf

	attributesToPreFile = staticmethod(attributesToPreFile)

	def attributesToPreFile(file):
		pf = PreFile()
		sAtributos = ""
		sName = file.Name.Replace("'", "''")
		pf.setName(sName)
		pf.setSize(file.Length)
		pf.setModified(file.LastWriteTime)
		sAtributos += "[ARQ]"
		if file.IsReadOnly:
			sAtributos += "[ROL]"
		if file.Attributes == FileAttributes.Hidden:
			sAtributos += "[HID]"
		if file.Attributes == FileAttributes.System:
			sAtributos += "[SYS]"
		pf.setAttributes(sAtributos)
		pf.setOriginalPath(file.FullName)
		pf.setDirectory(False)
		pf.setFormatedSize(VisitFoldersUtil.MountBigSize(pf.getSize()))
		pf.setFormatedModified(pf.getModified().ToString("dd/MM/yyyy hh:mm:ss"))
		return pf

	attributesToPreFile = staticmethod(attributesToPreFile)

	def TraverseDirs(lst, dir):
		try:
			enumerator = dir.GetDirectories().GetEnumerator()
			while enumerator.MoveNext():
				iInfo = enumerator.Current
				#if (iInfo.Name.EndsWith(fileSufix)){
				lst.Add(VisitFoldersUtil.attributesToPreFile(iInfo))
				#}
				VisitFoldersUtil.TraverseDirs(lst, iInfo)
		except Exception:
			pass
		finally:
			pass
		
		try:
			enumerator = dir.GetFiles().GetEnumerator()
			while enumerator.MoveNext():
				iInfo = enumerator.Current
				#if (iInfo.Name.EndsWith(fileSufix)){
				lst.Add(VisitFoldersUtil.attributesToPreFile(iInfo))
		except Exception:
			pass
		finally:
			pass
		
	TraverseDirs = staticmethod(TraverseDirs)