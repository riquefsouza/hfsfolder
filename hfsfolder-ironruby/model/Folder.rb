# 
# * Created by SharpDevelop.
# * User: henrique.souza
# * Date: 08/04/2019
# * Time: 14:04
# *
# * To change this template use Tools | Options | Coding | Edit Standard Headers.
# 
require "mscorlib"
require "System, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a"

module hfsfolder.model
	# <summary>
	# Description of Folder.
	# </summary>
	class Folder < PreFile, IComparable
		def initialize(preFile)
		end

		def getCode()
			return @code
		end

		def setCode(code)
			self.@code = code
		end

		def getOrder()
			return @order
		end

		def setOrder(order)
			self.@order = order
		end

		def getParentCodFolder()
			return @parentCodFolder
		end

		def setParentCodFolder(parentCodFolder)
			self.@parentCodFolder = parentCodFolder
		end

		def getFolderType()
			return @folderType
		end

		def setFolderType(folderType)
			self.@folderType = folderType
		end

		def getPath()
			return @path
		end

		def setPath(path)
			self.@path = path
		end

		def getParentName()
			return @parentName
		end

		def setParentName(parentName)
			self.@parentName = parentName
		end

		def getParentPath()
			return @parentPath
		end

		def setParentPath(parentPath)
			self.@parentPath = parentPath
		end

		def limparDados()
			self.limparDados()
			self.@code = 0
			self.@order = 0
			self.@parentCodFolder = 0
			self.@folderType = 'A'
			self.@path = ""
			self.@parentName = ""
			self.@parentPath = ""
		end

		def ToString()
			return "Folder [codigo=" + @code + ", ordem=" + @order + ", codDirPai=" + @parentCodFolder + ", tipo=" + @folderType + ", caminho=" + @path + ", nomePai=" + @parentName + ", caminhoPai=" + @parentPath + "]"
		end

		def ToInsert(naba)
			return "INSERT INTO Diretorios(aba, cod, ordem, nome, tam, tipo, modificado, atributos, coddirpai, caminho) VALUES(" + naba.ToString() + "," + @code + "," + @order + ",'" + self.getName() + "'," + self.getSize() + ",'" + @folderType + "','" + self.getFormatedModified() + "','" + self.getAttributes() + "'," + @parentCodFolder + ",'" + self.getPath() + "');"
		end

		def ToCVS()
			return @code + ";" + @order + ";" + self.getName() + ";" + self.getSize() + ";" + @folderType + ";" + self.getFormatedModified() + ";" + self.getAttributes() + ";" + @parentCodFolder + ";" + self.getPath()
		end

		def ToJSON()
			return "{\n  \"name\" : \"" + self.getName() + "\"," + "\n  \"size\" : " + self.getSize() + "," + "\n  \"modified\" : " + self.getModified() + "," + "\n  \"attributes\" : \"" + self.getAttributes() + "\"," + "\n  \"formatedSize\" : \"" + self.getFormatedSize() + "\"," + "\n  \"formatedModified\" : \"" + self.getFormatedModified() + "\"," + "\n  \"code\" : " + @code + "," + "\n  \"order\" : " + @order + "," + "\n  \"parentCodFolder\" : " + @parentCodFolder + "," + "\n  \"folderType\" : \"" + @folderType + "\"," + "\n  \"path\" : \"" + @path + "\"," + "\n  \"parentName\" : \"" + @parentName + "\"," + "\n  \"parentPath\" : \"" + @parentPath + "\"," + "\n  \"originalPath\" : \"" + self.getOriginalPath() + "\"\n}"
		end

		def CompareTo(obj)
			otherFolder = obj
			if otherFolder == nil then
				return -1
			end
			return @path.CompareTo(otherFolder.getPath())
		end
	end
end