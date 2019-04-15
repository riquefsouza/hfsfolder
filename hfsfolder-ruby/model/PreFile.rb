# 
# * User: henrique.souza
# * Date: 08/04/2019
# * Time: 14:00

class PreFile

  def initialize
    self.limparDados
  end

  def getName
    @name
  end

  def setName(name)
    @name = name
  end

  def getSize
    @size
  end

  def setSize(size)
    @size = size
  end

  def getModified
    @modified
  end

  def setModified(modified)
    @modified = modified
  end

  def getAttributes
    @attributes
  end

  def setAttributes(attributes)
    @attributes = attributes
  end

  def getFormatedSize
    @formatedSize
  end

  def setFormatedSize(formatedSize)
    @formatedSize = formatedSize
  end

  def getFormatedModified
    @formatedModified
  end

  def setFormatedModified(formatedModified)
    @formatedModified = formatedModified
  end

  def getOriginalPath
    @originalPath
  end

  def setOriginalPath(originalPath)
    @originalPath = originalPath
  end

  def isDirectory
    @directory
  end

  def setDirectory(directory)
    @directory = directory
  end

  def limparDados
    @name = ""
    @size = 0
    @modified = Time.now
    @attributes = ""
    @formatedSize = ""
    @formatedModified = ""
    @originalPath = ""
    @directory = false
  end

  def toString
    "PreFile [name=" + @name + ", size=" + @size.to_s +
        ", modified=" + @modified.to_s + ", attributes=" + @attributes +
        ", formatSize=" + @formatedSize + ", formatModified=" + @formatedModified + "]"
  end

  def toInsert
    "'" + getName + "'," + @size.to_s + ",'" + @formatedModified + "','" + @attributes + "'"
  end

  def toCVS
    getName + ";" + @size.to_s + ";" + @formatedModified + ";" + @attributes
  end
end
