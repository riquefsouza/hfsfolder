# 
# * Created by SharpDevelop.
# * User: henrique.souza
# * Date: 08/04/2019
# * Time: 14:04
# *
# * To change this template use Tools | Options | Coding | Edit Standard Headers.
# 
from System import *

class Folder(PreFile, IComparable):
	""" <summary>
	 Description of Folder.
	 </summary>
	"""
	def __init__(self, preFile):
		pass
	
	def getCode(self):
		return self._code

	def setCode(self, code):
		self._code = code

	def getOrder(self):
		return self._order

	def setOrder(self, order):
		self._order = order

	def getParentCodFolder(self):
		return self._parentCodFolder

	def setParentCodFolder(self, parentCodFolder):
		self._parentCodFolder = parentCodFolder

	def getFolderType(self):
		return self._folderType

	def setFolderType(self, folderType):
		self._folderType = folderType

	def getPath(self):
		return self._path

	def setPath(self, path):
		self._path = path

	def getParentName(self):
		return self._parentName

	def setParentName(self, parentName):
		self._parentName = parentName

	def getParentPath(self):
		return self._parentPath

	def setParentPath(self, parentPath):
		self._parentPath = parentPath

	def limparDados(self):
		self.limparDados()
		self._code = 0
		self._order = 0
		self._parentCodFolder = 0
		self._folderType = 'A'
		self._path = ""
		self._parentName = ""
		self._parentPath = ""

	def ToString(self):
		return "Folder [codigo=" + self._code + ", ordem=" + self._order + ", codDirPai=" + self._parentCodFolder + ", tipo=" + self._folderType + ", caminho=" + self._path + ", nomePai=" + self._parentName + ", caminhoPai=" + self._parentPath + "]"

	def ToInsert(self, naba):
		return "INSERT INTO Diretorios(aba, cod, ordem, nome, tam, tipo, modificado, atributos, coddirpai, caminho) VALUES(" + naba.ToString() + "," + self._code + "," + self._order + ",'" + self.getName() + "'," + self.getSize() + ",'" + self._folderType + "','" + self.getFormatedModified() + "','" + self.getAttributes() + "'," + self._parentCodFolder + ",'" + self.getPath() + "');"

	def ToCVS(self):
		return self._code + ";" + self._order + ";" + self.getName() + ";" + self.getSize() + ";" + self._folderType + ";" + self.getFormatedModified() + ";" + self.getAttributes() + ";" + self._parentCodFolder + ";" + self.getPath()

	def ToJSON(self):
		return "{\n  \"name\" : \"" + self.getName() + "\"," + "\n  \"size\" : " + self.getSize() + "," + "\n  \"modified\" : " + self.getModified() + "," + "\n  \"attributes\" : \"" + self.getAttributes() + "\"," + "\n  \"formatedSize\" : \"" + self.getFormatedSize() + "\"," + "\n  \"formatedModified\" : \"" + self.getFormatedModified() + "\"," + "\n  \"code\" : " + self._code + "," + "\n  \"order\" : " + self._order + "," + "\n  \"parentCodFolder\" : " + self._parentCodFolder + "," + "\n  \"folderType\" : \"" + self._folderType + "\"," + "\n  \"path\" : \"" + self._path + "\"," + "\n  \"parentName\" : \"" + self._parentName + "\"," + "\n  \"parentPath\" : \"" + self._parentPath + "\"," + "\n  \"originalPath\" : \"" + self.getOriginalPath() + "\"\n}"

	def CompareTo(self, obj):
		otherFolder = obj
		if otherFolder == None:
			return -1
		return self._path.CompareTo(otherFolder.getPath())