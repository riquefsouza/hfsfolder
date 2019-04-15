# 
# * Created by SharpDevelop.
# * User: henrique.souza
# * Date: 08/04/2019
# * Time: 14:52
# *
# * To change this template use Tools | Options | Coding | Edit Standard Headers.
#
import re
from model.Folder import Folder
from model.FolderOrder import FolderOrder
from util.VisitFoldersUtil import VisitFoldersUtil


class ProcessFolders:
	""" <summary>
	 Description of ProcessFolders.
	 </summary>
	"""
	def createFolder(self, pf, folderOrder):
		folder = Folder(pf)
		if pf.isDirectory():
			folder.setFolderType('D')
		else:
			folder.setFolderType('A')
		sPath = pf.getOriginalPath()
		if re.match("[a-zA-Z]:\\\\", sPath):
			sPath = sPath[3:]
			folder.separatorChar = '\\'
		if re.match( "[a-zA-Z]:/", sPath):
			sPath = sPath[3:]
			folder.separatorChar = '/'
		if sPath.startswith("/"):
			sPath = sPath[1:]
			folder.separatorChar = '/'
		folder.setPath(sPath.replace("'", "''").replace("\\", "/"))
		folder.setOriginalPath(pf.getOriginalPath())
		if folder.getPath().count("/") == 0:
			folderOrder.setCodFolder(folderOrder.getCodFolder() + 1)
			folderOrder.setOrder(1)
		else:
			folderOrder.setOrder(folderOrder.getOrder() + 1)
		folder.setCode(folderOrder.getCodFolder())
		folder.setOrder(folderOrder.getOrder())
		return folder

	def process(self, folder):
		listaFolders = []
		folderOrder = FolderOrder(-1, 0)
		print("Processing folders!")
		vfu = VisitFoldersUtil()
		listaPrefiles = vfu.getListFromFiles(folder)

		for pf in listaPrefiles:
			dir = self.createFolder(pf, folderOrder)
			listaFolders.append(dir)

		for item in listaFolders:
			lastIndex = item.getOriginalPath().rindex(item.separatorChar)
			pathChild = item.getOriginalPath()[0:lastIndex]

			pathFather = list(filter(lambda f: f.getOriginalPath()==pathChild, listaFolders))

			if len(pathFather) > 0:
				item.setParentCodFolder(pathFather[0].getOrder())
				item.setParentName(pathFather[0].getName())
				item.setParentPath(pathFather[0].getPath())
			else:
				item.setParentCodFolder(0)
				item.setParentName("")
				item.setParentPath("")

		listaFolders.sort(key=lambda f: f.getPath())

		return listaFolders

	def processFoldersToJson(self, folder):
		lista = self.process(folder)
		result = "[ "
		for i in range(0, len(lista)):
			item = lista[i]
			if i == 0:
				result += item.toJSON()
			else:
				result += ", " + item.toJSON()

		return result + " ]"

	def processFoldersToFile(self, data, sfile):
		f = open(sfile, "a")
		f.write(data)
		f.close()

	def processFoldersToInsert(self, folder, naba):
		lista = self.process(folder)
		result = ""
		for item in lista:
			result += item.toInsert(naba) + "\n"
		return result

	def processFoldersToCSV(self, folder):
		lista = self.process(folder)
		result = f'Code;Order;Name;Size;"Folder Type";"Formated Modified";Attributes;"Parent Code Folder";Path\n'
		for item in lista:
			result += item.toCVS() + "\n"
		return result