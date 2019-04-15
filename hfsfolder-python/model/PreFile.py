# 
# * Created by SharpDevelop.
# * User: henrique.souza
# * Date: 08/04/2019
# * Time: 14:00
# *
# * To change this template use Tools | Options | Coding | Edit Standard Headers.
#
from datetime import datetime

class PreFile:
	""" <summary>
	 Description of PreFile.
	 </summary>
	"""
	def __init__(self):
		self.limparDados()

	def getName(self):
		return self._name

	def setName(self, name):
		self._name = name

	def getSize(self):
		return self._size

	def setSize(self, size):
		self._size = size

	def getModified(self):
		return self._modified

	def setModified(self, modified):
		self._modified = modified

	def getAttributes(self):
		return self._attributes

	def setAttributes(self, attributes):
		self._attributes = attributes

	def getFormatedSize(self):
		return self._formatedSize

	def setFormatedSize(self, formatedSize):
		self._formatedSize = formatedSize

	def getFormatedModified(self):
		return self._formatedModified

	def setFormatedModified(self, formatedModified):
		self._formatedModified = formatedModified

	def getOriginalPath(self):
		return self._originalPath

	def setOriginalPath(self, originalPath):
		self._originalPath = originalPath

	def isDirectory(self):
		return self._directory

	def setDirectory(self, directory):
		self._directory = directory

	def limparDados(self):
		self._name = ""
		self._size = 0
		self._modified = datetime.now()
		self._attributes = ""
		self._formatedSize = ""
		self._formatedModified = ""
		self._originalPath = ""
		self._directory = False

	def toString(self):
		return f"PreFile [name={self._name}, size={self._size}, " \
			f"modified={self._modified}, attributes={self._attributes}, " \
			f"formatSize={self._formatedSize}, formatModified={self._formatedModified}]"

	def toInsert(self):
		return f"'{self.getName()}',{self._size},'{self._formatedModified}','{self._attributes}'"

	def toCVS(self):
		return f"{self.getName()};{self._size};{self._formatedModified};{self._attributes}"