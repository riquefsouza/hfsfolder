# 
# * User: henrique.souza
# * Date: 08/04/2019
# * Time: 14:52
#
require_relative 'model/FolderOrder'
require_relative 'model/Folder'
require_relative 'util/VisitFoldersUtil'

class ProcessFolders

  def createFolder(pf, folderOrder)
    folder = Folder.new(pf)

    if pf.isDirectory
      folder.setFolderType('D')
    else
      folder.setFolderType('A')
    end

    sPath = pf.getOriginalPath
    regex = /[a-zA-Z]:\\/
    if regex.match(sPath)
      sPath = sPath.slice(3, sPath.length)
      folder.separatorChar = '\\'
    end
    regex = /[a-zA-Z]:\//
    if regex.match(sPath)
      sPath = sPath.slice(3, sPath.length)
      folder.separatorChar = '/'
    end
    if sPath.start_with?("/")
      sPath = sPath.slice(1, sPath.length)
      folder.separatorChar = '/'
    end

    folder.setPath(sPath.gsub("'", "''").gsub("\\", "/"))
    folder.setOriginalPath(pf.getOriginalPath)

    if not folder.getPath.include?("/")
      folderOrder.setCodFolder(folderOrder.getCodFolder + 1)
      folderOrder.setOrder(1)
    else
      folderOrder.setOrder(folderOrder.getOrder + 1)
    end

    folder.setCode(folderOrder.getCodFolder)
    folder.setOrder(folderOrder.getOrder)

    folder
  end

  def process(folder)
    listaFolders = []
    folderOrder = FolderOrder.new(-1, 0)
    puts "Processing folders!"
    vfu = VisitFoldersUtil.new
    listaPrefiles = vfu.getListFromFiles(folder)

    listaPrefiles.each do |pf|
      dir = self.createFolder(pf, folderOrder)
      listaFolders.push(dir)
    end

    listaFolders.each do |item|
      lastIndex = item.getOriginalPath.rindex(item.separatorChar)
      pathChild = item.getOriginalPath.slice(0, lastIndex)

      pathFather = listaFolders.detect do |f|
        f.getOriginalPath == pathChild
      end

      if pathFather != nil
        item.setParentCodFolder(pathFather.getOrder)
        item.setParentName(pathFather.getName)
        item.setParentPath(pathFather.getPath)
      else
        item.setParentCodFolder(0)
        item.setParentName("")
        item.setParentPath("")
      end

    end

    listaFolders.sort {|s1,s2| s1.getPath <=> s2.getPath}

    listaFolders
  end

  def processFoldersToJson(folder)
    lista = self.process(folder)
    result = "[ "

    (0..lista.length-1).each {|i|
      item = lista[i]
      if i == 0
        result += item.toJSON
      else
        result += ", " + item.toJSON
      end
    }

    result + " ]"
  end

  def processFoldersToFile(data, sfile)
    aFile = File.open(sfile, "w")
    if aFile
      aFile.puts data
    else
      puts "Unable to open file!"
    end
    aFile.close
  end

  def processFoldersToInsert(folder, naba)
    lista = self.process(folder)
    result = ""
    lista.each do |item|
      result += item.toInsert(naba) + "\n"
    end
    result
  end

  def processFoldersToCSV(folder)
    lista = self.process(folder)
    result = 'Code;Order;Name;Size;"Folder Type";"Formated Modified";Attributes;"Parent Code Folder";Path\n'
    lista.each do |item|
      result += item.toCVS + "\n"
    end
    result
  end

end