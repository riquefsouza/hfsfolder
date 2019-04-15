# 
# * Created by SharpDevelop.
# * User: henrique.souza
# * Date: 08/04/2019
# * Time: 14:04
# *
# * To change this template use Tools | Options | Coding | Edit Standard Headers.
#
from model.PreFile import PreFile

class Folder(PreFile):
	""" <summary>
	 Description of Folder.
	 </summary>
	"""
	def __init__(self, preFile):
		self.setName(preFile.getName())
		self.setSize(preFile.getSize())
		self.setModified(preFile.getModified())
		self.setAttributes(preFile.getAttributes())
		self.setFormatedSize(preFile.getFormatedSize())
		self.setFormatedModified(preFile.getFormatedModified())
	
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

	def toString(self):
		return f"Folder [codigo={self._code}, ordem={self._order}, codDirPai={self._parentCodFolder}, " \
			f"tipo={self._folderType}, caminho={self._path}, nomePai={self._parentName}, " \
			f"caminhoPai={self._parentPath}]"

	def toInsert(self, naba):
		return f"INSERT INTO Diretorios(aba, cod, ordem, nome, tam, tipo, modificado, atributos, coddirpai, caminho) " \
			f"VALUES({naba.ToString()},{self._code},{self._order},'{self.getName()}'," \
			f"{self.getSize()},'{self._folderType}','{self.getFormatedModified()}','" \
			f"{self.getAttributes()}',{self._parentCodFolder},'{self.getPath()}');"

	def toCVS(self):
		return f"{self._code};{self._order};{self.getName()};{self.getSize()};" \
			f"{self._folderType};{self.getFormatedModified()};{self.getAttributes()};" \
			f"{self._parentCodFolder};{self.getPath()}"

	def toJSON(self):
		str = f'{{\n  "name" : "{self.getName()}",'
		str += f'\n  "size" : {self.getSize()},'
		str += f'\n  "modified" : {self.getModified()},'
		str += f'\n  "attributes" : "{self.getAttributes()}",'
		str += f'\n  "formatedSize" : {self.getFormatedSize()},'
		str += f'\n  "formatedModified" : "{self.getFormatedModified()}",'
		str += f'\n  "code" : {self._code},'
		str += f'\n  "order" : {self._order},'
		str += f'\n  "parentCodFolder" : {self._parentCodFolder},'
		str += f'\n  "folderType" : "{self._folderType}",'
		str += f'\n  "path" : "{self._path}",'
		str += f'\n  "parentName" : "{self._parentName}",'
		str += f'\n  "parentPath" : "{self._parentPath}",'
		str += f'\n  "originalPath" : "{self.getOriginalPath()}"\n}}'

		return str