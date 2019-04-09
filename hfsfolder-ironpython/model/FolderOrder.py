# 
# * Created by SharpDevelop.
# * User: henrique.souza
# * Date: 08/04/2019
# * Time: 13:52
# *
# * To change this template use Tools | Options | Coding | Edit Standard Headers.
# 
from System import *

class FolderOrder(object):
	""" <summary>
	 Description of FolderOrder.
	 </summary>
	"""
	def __init__(self, folderOrder):
		self._codFolder = folderOrder.getCodFolder()
		self._order = folderOrder.getOrder()

	def __init__(self, folderOrder):
		self._codFolder = folderOrder.getCodFolder()
		self._order = folderOrder.getOrder()

	def getCodFolder(self):
		return self._codFolder

	def setCodFolder(self, codFolder):
		self._codFolder = codFolder

	def getOrder(self):
		return self._order

	def setOrder(self, order):
		self._order = order