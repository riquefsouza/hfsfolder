# 
# * Created by SharpDevelop.
# * User: henrique.souza
# * Date: 08/04/2019
# * Time: 14:09
# *
# * To change this template use Tools | Options | Coding | Edit Standard Headers.
#
import fnmatch
import os
from datetime import datetime
#from os.path import join, getsize
from model.PreFile import PreFile

class VisitFoldersUtil:
	""" <summary>
	 Description of VisitFoldersUtil.
	 </summary>
	"""
	def getListFromFiles(self, folder):
		lst = []
		filename = os.path.basename(folder)
		prefile = self.attributesToPreFile(folder, filename)
		lst.append(prefile)
		for root, dirs, files in os.walk(folder):
			for dfolder in dirs:
				sdir = os.path.join(root, dfolder)
				prefile = self.attributesToPreFile(sdir, dfolder)
				lst.append(prefile)
			for filename in files:
				sfile = os.path.join(root, filename)
				prefile = self.attributesToPreFile(sfile, filename)
				lst.append(prefile)
		return lst

	def getListFromFilesByPattern(self, folder, pattern):
		lst = []
		for root, dirs, files in os.walk(folder):
			for dfolder in dirs:
				sdir = os.path.join(root, dfolder)
				prefile = self.attributesToPreFile(sdir, dfolder)
				lst.append(prefile)
			for filename in fnmatch.filter(files, pattern):
				sfile = os.path.join(root, filename)
				prefile = self.attributesToPreFile(sfile, filename)
				lst.append(prefile)
		return lst

	def formatDecimal(self, valor):
		return '{:.2f}'.format(valor)

	def mountBigSize(self, nTam):
		nUmKilo = 1024
		nUmMega = nUmKilo * 1024
		nUmGiga = nUmMega * 1024
		nUmTera = nUmGiga * 1024
		nUmPeta = nUmTera * 1024
		if nTam < nUmKilo:
			nTamLocal = float(nTam)
			return self.formatDecimal(nTamLocal) + " Byte(s)"
		elif nTam > nUmKilo and nTam < nUmMega:
			nTamLocal = float(nTam / nUmKilo)
			return self.formatDecimal(nTamLocal) + " KByte(s)"
		elif nTam > nUmMega and nTam < nUmGiga:
			nTamLocal = float(nTam / nUmMega)
			return self.formatDecimal(nTamLocal) + " MByte(s)"
		elif nTam < nUmGiga and nTam > nUmTera:
			nTamLocal = float(nTam / nUmGiga)
			return self.formatDecimal(nTamLocal) + " GByte(s)"
		elif nTam < nUmTera and nTam > nUmPeta:
			nTamLocal = float(nTam / nUmTera)
			return self.formatDecimal(nTamLocal) + " TByte(s)"
		else:
			nTamLocal = float(nTam / nUmPeta)
			return self.formatDecimal(nTamLocal) + " PByte(s)"

	def attributesToPreFile(self, sfile, filename):
		pf = PreFile()
		sAtributos = ""
		sName = filename.replace("'", "''")
		pf.setName(sName)
		pf.setSize(os.path.getsize(sfile))
		try:
			mtime = os.path.getmtime(sfile)
			pf.setModified(datetime.fromtimestamp(mtime))
		except OSError:
			pf.setModified(datetime.now())

		if (os.path.isdir(sfile)):
			sAtributos += "[DIR]"
			pf.setDirectory(True)
		else:
			sAtributos += "[ARQ]"
			pf.setDirectory(False)

		pf.setAttributes(sAtributos)
		pf.setOriginalPath(sfile)
		pf.setFormatedSize(self.mountBigSize(pf.getSize()))
		pf.setFormatedModified('{:%d/%m/%Y %H:%M:%S}'.format(pf.getModified()))
		return pf