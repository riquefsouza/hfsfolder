# * User: henrique.souza
# * Date: 08/04/2019
# * Time: 14:04

require_relative 'PreFile'

class Folder < PreFile

  def initialize(preFile)
    self.setName(preFile.getName)
    self.setSize(preFile.getSize)
    self.setModified(preFile.getModified)
    self.setAttributes(preFile.getAttributes)
    self.setFormatedSize(preFile.getFormatedSize)
    self.setFormatedModified(preFile.getFormatedModified)
    self.separatorChar = '/'
  end

  def getCode
    @code
  end

  def setCode(code)
    @code = code
  end

  def getOrder
    @order
  end

  def setOrder(order)
    @order = order
  end

  def getParentCodFolder
    @parentCodFolder
  end

  def setParentCodFolder(parentCodFolder)
    @parentCodFolder = parentCodFolder
  end

  def getFolderType
    @folderType
  end

  def setFolderType(folderType)
    @folderType = folderType
  end

  def getPath
    @path
  end

  def setPath(path)
    @path = path
  end

  def getParentName
    @parentName
  end

  def setParentName(parentName)
    @parentName = parentName
  end

  def getParentPath
    @parentPath
  end

  def setParentPath(parentPath)
    @parentPath = parentPath
  end

  def limparDados
    self.limparDados
    @code = 0
    @order = 0
    @parentCodFolder = 0
    @folderType = 'A'
    @path = ""
    @parentName = ""
    @parentPath = ""
  end

  def toString
    "Folder [codigo=" + @code.to_s + ", ordem=" + @order.to_s + ", codDirPai=" + @parentCodFolder.to_s + ", tipo=" +
        @folderType + ", caminho=" + @path + ", nomePai=" + @parentName + ", caminhoPai=" + @parentPath + "]"
  end

  def toInsert(naba)
    "INSERT INTO Diretorios(aba, cod, ordem, nome, tam, tipo, modificado, atributos, coddirpai, caminho) VALUES(" +
        naba.to_s + "," + @code.to_s + "," + @order.to_s + ",'" + getName + "'," + getSize.to_s + ",'" + @folderType + "','" +
        getFormatedModified + "','" + getAttributes + "'," + @parentCodFolder.to_s + ",'" + getPath + "');"
  end

  def toCVS
    @code.to_s + ";" + @order.to_s + ";" + getName + ";" + getSize.to_s + ";" + @folderType + ";" + getFormatedModified +
        ";" + getAttributes + ";" + @parentCodFolder.to_s + ";" + getPath
  end

  def toJSON
    "{\n  \"name\" : \"" + getName + "\"," + "\n  \"size\" : " + getSize.to_s + "," +
        "\n  \"modified\" : " + getModified.to_s + "," + "\n  \"attributes\" : \"" + getAttributes + "\"," +
        "\n  \"formatedSize\" : \"" + getFormatedSize + "\"," +
        "\n  \"formatedModified\" : \"" + getFormatedModified + "\"," + "\n  \"code\" : " + @code.to_s + "," +
        "\n  \"order\" : " + @order.to_s + "," + "\n  \"parentCodFolder\" : " + @parentCodFolder.to_s + "," +
        "\n  \"folderType\" : \"" + @folderType + "\"," + "\n  \"path\" : \"" + @path + "\"," +
        "\n  \"parentName\" : \"" + @parentName + "\"," + "\n  \"parentPath\" : \"" + @parentPath + "\"," +
        "\n  \"originalPath\" : \"" + getOriginalPath + "\"\n}"
  end

  def separatorChar
    @separatorChar
  end

  def separatorChar=(value)
    @separatorChar = value
  end

end
