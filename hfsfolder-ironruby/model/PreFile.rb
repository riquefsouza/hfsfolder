# 
# * Created by SharpDevelop.
# * User: henrique.souza
# * Date: 08/04/2019
# * Time: 14:00
# *
# * To change this template use Tools | Options | Coding | Edit Standard Headers.
# 
require "mscorlib"
require "System, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a"

module hfsfolder.model
	# <summary>
	# Description of PreFile.
	# </summary>
	class PreFile
		def initialize(name, size, modified, attributes, formatSize, formatModified)
			self.@name = name
			self.@size = size
			self.@modified = modified
			self.@attributes = attributes
			self.@formatedSize = formatSize
			self.@formatedModified = formatModified
		end

		def initialize(name, size, modified, attributes, formatSize, formatModified)
			self.@name = name
			self.@size = size
			self.@modified = modified
			self.@attributes = attributes
			self.@formatedSize = formatSize
			self.@formatedModified = formatModified
		end

		def getName()
			return @name
		end

		def setName(name)
			self.@name = name
		end

		def getSize()
			return @size
		end

		def setSize(size)
			self.@size = size
		end

		def getModified()
			return @modified
		end

		def setModified(modified)
			self.@modified = modified
		end

		def getAttributes()
			return @attributes
		end

		def setAttributes(attributes)
			self.@attributes = attributes
		end

		def getFormatedSize()
			return @formatedSize
		end

		def setFormatedSize(formatedSize)
			self.@formatedSize = formatedSize
		end

		def getFormatedModified()
			return @formatedModified
		end

		def setFormatedModified(formatedModified)
			self.@formatedModified = formatedModified
		end

		def getOriginalPath()
			return @originalPath
		end

		def setOriginalPath(originalPath)
			self.@originalPath = originalPath
		end

		def isDirectory()
			return @directory
		end

		def setDirectory(directory)
			self.@directory = directory
		end

		def limparDados()
			self.@name = ""
			self.@size = 0
			self.@modified = DateTime.Now
			self.@attributes = ""
			self.@formatedSize = ""
			self.@formatedModified = ""
			self.@originalPath = ""
			self.@directory = false
		end

		def ToString()
			return "PreFile [name=" + @name + ", size=" + @size + ", modified=" + @modified + ", attributes=" + @attributes + ", formatSize=" + @formatedSize + ", formatModified=" + @formatedModified + "]"
		end

		def ToInsert()
			return "'" + self.getName() + "'," + @size + ",'" + @formatedModified + "','" + @attributes + "'"
		end

		def ToCVS()
			return self.getName() + ";" + @size + ";" + @formatedModified + ";" + @attributes
		end
	end
end