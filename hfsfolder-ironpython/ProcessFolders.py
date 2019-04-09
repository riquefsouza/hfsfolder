# 
# * Created by SharpDevelop.
# * User: henrique.souza
# * Date: 08/04/2019
# * Time: 14:52
# *
# * To change this template use Tools | Options | Coding | Edit Standard Headers.
# 
from System import *
from System.IO import *
from System.Text import *
from System.Text.RegularExpressions import *
from System.Collections.Generic import *
from hfsfolder.model import *
from hfsfolder.util import *

class ProcessFolders(object):
	""" <summary>
	 Description of ProcessFolders.
	 </summary>
	"""
	def createFolder(pf, folderOrder):
		folder = Folder(pf)
		if pf.isDirectory():
			folder.setFolderType('D')
		else:
			folder.setFolderType('A')
		sPath = pf.getOriginalPath()
		if Regex.IsMatch(sPath, "[a-zA-Z]:\\\\"):
			sPath = sPath.Substring(3)
			folder.separatorChar = '\\'
		if Regex.IsMatch(sPath, "[a-zA-Z]:/"):
			sPath = sPath.Substring(3)
			folder.separatorChar = '/'
		if sPath.StartsWith("/"):
			sPath = sPath.Substring(1)
			folder.separatorChar = '/'
		folder.setPath(sPath.Replace("'", "''").Replace("\\", "/"))
		folder.setOriginalPath(pf.getOriginalPath())
		if not folder.getPath().Contains("/"):
			folderOrder.setCodFolder(folderOrder.getCodFolder() + 1)
			folderOrder.setOrder(1)
		else:
			folderOrder.setOrder(folderOrder.getOrder() + 1)
		folder.setCode(folderOrder.getCodFolder())
		folder.setOrder(folderOrder.getOrder())
		return folder

	createFolder = staticmethod(createFolder)

	def process(folder):
		listaFolders = List[Folder]()
		folderOrder = FolderOrder(-1, 0)
		Console.WriteLine("Processing folders!")
		listaPrefiles = VisitFoldersUtil.getListFromFiles(folder)
		enumerator = listaPrefiles.GetEnumerator()
		while enumerator.MoveNext():
			pf = enumerator.Current
			dir = ProcessFolders.createFolder(pf, folderOrder)
			listaFolders.Add(dir)
		enumerator = listaFolders.GetEnumerator()
		while enumerator.MoveNext():
			item = enumerator.Current
			pathChild = item.getOriginalPath().Substring(0, item.getOriginalPath().LastIndexOf(item.separatorChar))
			pathFather = listaFolders.Find()
			if pathFather != None:
				item.setParentCodFolder(pathFather.getOrder())
				item.setParentName(pathFather.getName())
				item.setParentPath(pathFather.getPath())
		listaFolders.Sort()
		return listaFolders

	process = staticmethod(process)

	def processFoldersToJson(folder):
		lista = ProcessFolders.process(folder)
		result = "[ "
		i = 0
		while i < lista.Count:
			item = lista[i]
			if i == 0:
				result += item.ToJSON()
			else:
				result += ", " + item.ToJSON()
			i += 1
		return result + " ]"

	processFoldersToJson = staticmethod(processFoldersToJson)

	def processFoldersToFile(data, sfile):
		fileStream = None
		try:
			fileStream = FileStream(sfile, FileMode.OpenOrCreate, FileAccess.Write)
			fileStream.Write(Encoding.Default.GetBytes(data), 0, data.Length)
			fileStream.Flush()
		except FileNotFoundException, ioEx:
			Console.WriteLine(ioEx.Message)
		finally:
			if fileStream != None:
				fileStream.Close()

	processFoldersToFile = staticmethod(processFoldersToFile)

	def processFoldersToInsert(folder, naba):
		lista = ProcessFolders.process(folder)
		result = ""
		enumerator = lista.GetEnumerator()
		while enumerator.MoveNext():
			item = enumerator.Current
			result += item.ToInsert(naba) + "\n"
		return result

	processFoldersToInsert = staticmethod(processFoldersToInsert)

	def processFoldersToCSV(folder):
		lista = ProcessFolders.process(folder)
		result = "Code;Order;Name;Size;\"Folder Type\";\"Formated Modified\";Attributes;\"Parent Code Folder\";Path\n"
		enumerator = lista.GetEnumerator()
		while enumerator.MoveNext():
			item = enumerator.Current
			result += item.ToCVS() + "\n"
		return result

	processFoldersToCSV = staticmethod(processFoldersToCSV)