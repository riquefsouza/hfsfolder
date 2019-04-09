# 
# * Created by SharpDevelop.
# * User: henrique.souza
# * Date: 08/04/2019
# * Time: 14:52
# *
# * To change this template use Tools | Options | Coding | Edit Standard Headers.
# 
require "mscorlib"
require "System, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a"
require "System.IO, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a"
require "System.Text, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a"
require "System.Text.RegularExpressions, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a"
require "System.Collections.Generic, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a"
require "hfsfolder.model, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a"
require "hfsfolder.util, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a"

module hfsfolder
	# <summary>
	# Description of ProcessFolders.
	# </summary>
	class ProcessFolders
		def ProcessFolders.createFolder(pf, folderOrder)
			folder = Folder.new(pf)
			if pf.isDirectory() then
				folder.setFolderType('D')
			else
				folder.setFolderType('A')
			end
			sPath = pf.getOriginalPath()
			if Regex.IsMatch(sPath, "[a-zA-Z]:\\\\") then
				sPath = sPath.Substring(3)
				folder.separatorChar = '\\'
			end
			if Regex.IsMatch(sPath, "[a-zA-Z]:/") then
				sPath = sPath.Substring(3)
				folder.separatorChar = '/'
			end
			if sPath.StartsWith("/") then
				sPath = sPath.Substring(1)
				folder.separatorChar = '/'
			end
			folder.setPath(sPath.Replace("'", "''").Replace("\\", "/"))
			folder.setOriginalPath(pf.getOriginalPath())
			if not folder.getPath().Contains("/") then
				folderOrder.setCodFolder(folderOrder.getCodFolder() + 1)
				folderOrder.setOrder(1)
			else
				folderOrder.setOrder(folderOrder.getOrder() + 1)
			end
			folder.setCode(folderOrder.getCodFolder())
			folder.setOrder(folderOrder.getOrder())
			return folder
		end

		def ProcessFolders.process(folder)
			listaFolders = List[Folder].new()
			folderOrder = FolderOrder.new(-1, 0)
			Console.WriteLine("Processing folders!")
			listaPrefiles = VisitFoldersUtil.getListFromFiles(folder)
			enumerator = listaPrefiles.GetEnumerator()
			while enumerator.MoveNext()
				pf = enumerator.Current
				dir = ProcessFolders.createFolder(pf, folderOrder)
				listaFolders.Add(dir)
			end
			enumerator = listaFolders.GetEnumerator()
			while enumerator.MoveNext()
				item = enumerator.Current
				pathChild = item.getOriginalPath().Substring(0, item.getOriginalPath().LastIndexOf(item.separatorChar))
				pathFather = listaFolders.Find(f.getOriginalPath().Equals(pathChild))
				if pathFather != nil then
					item.setParentCodFolder(pathFather.getOrder())
					item.setParentName(pathFather.getName())
					item.setParentPath(pathFather.getPath())
				end
			end
			listaFolders.Sort()
			return listaFolders
		end

		def ProcessFolders.processFoldersToJson(folder)
			lista = ProcessFolders.process(folder)
			result = "[ "
			i = 0
			while i < lista.Count
				item = lista[i]
				if i == 0 then
					result += item.ToJSON()
				else
					result += ", " + item.ToJSON()
				end
				i += 1
			end
			return result + " ]"
		end

		def ProcessFolders.processFoldersToFile(data, sfile)
			fileStream = nil
			begin
				fileStream = FileStream.new(sfile, FileMode.OpenOrCreate, FileAccess.Write)
				fileStream.Write(Encoding.Default.GetBytes(data), 0, data.Length)
				fileStream.Flush()
			rescue FileNotFoundException => ioEx
				Console.WriteLine(ioEx.Message)
			ensure
				if fileStream != nil then
					fileStream.Close()
				end
			end
		end

		def ProcessFolders.processFoldersToInsert(folder, naba)
			lista = ProcessFolders.process(folder)
			result = ""
			enumerator = lista.GetEnumerator()
			while enumerator.MoveNext()
				item = enumerator.Current
				result += item.ToInsert(naba) + "\n"
			end
			return result
		end

		def ProcessFolders.processFoldersToCSV(folder)
			lista = ProcessFolders.process(folder)
			result = "Code;Order;Name;Size;\"Folder Type\";\"Formated Modified\";Attributes;\"Parent Code Folder\";Path\n"
			enumerator = lista.GetEnumerator()
			while enumerator.MoveNext()
				item = enumerator.Current
				result += item.ToCVS() + "\n"
			end
			return result
		end
	end
end