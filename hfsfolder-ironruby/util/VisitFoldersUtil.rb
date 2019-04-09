# 
# * Created by SharpDevelop.
# * User: henrique.souza
# * Date: 08/04/2019
# * Time: 14:09
# *
# * To change this template use Tools | Options | Coding | Edit Standard Headers.
# 
require "mscorlib"
require "System, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a"
require "System.IO, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a"
require "System.Collections.Generic, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a"
require "hfsfolder.model, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a"

module hfsfolder.util
	# <summary>
	# Description of VisitFoldersUtil.
	# </summary>
	class VisitFoldersUtil
		def VisitFoldersUtil.getListFromFiles(folder)
			lst = List[PreFile].new()
			dir = DirectoryInfo.new(folder)
			lst.Add(VisitFoldersUtil.attributesToPreFile(dir))
			VisitFoldersUtil.TraverseDirs(lst, dir)
			return lst
		end

		def VisitFoldersUtil.FormatDecimal(valor)
			return valor.ToString("#,##0.00")
		end

		def VisitFoldersUtil.MountBigSize(nTam)
			nUmKilo = 1024
			nUmMega = nUmKilo * 1024
			nUmGiga = nUmMega * 1024
			nUmTera = nUmGiga * 1024
			nUmPeta = nUmTera * 1024
			if nTam.CompareTo(nUmKilo) == -1 then
				nTamLocal = nTam
				return VisitFoldersUtil.FormatDecimal(nTamLocal) + " Byte(s)"
			elsif nTam.CompareTo(nUmKilo) == 1 and nTam.CompareTo(nUmMega) == -1 then
				nTamLocal = nTam / nUmKilo
				return VisitFoldersUtil.FormatDecimal(nTamLocal) + " KByte(s)"
			elsif nTam.CompareTo(nUmMega) == 1 and nTam.CompareTo(nUmGiga) == -1 then
				nTamLocal = nTam / nUmMega
				return VisitFoldersUtil.FormatDecimal(nTamLocal) + " MByte(s)"
			elsif nTam.CompareTo(nUmGiga) == 1 and nTam.CompareTo(nUmTera) == -1 then
				nTamLocal = nTam / nUmGiga
				return VisitFoldersUtil.FormatDecimal(nTamLocal) + " GByte(s)"
			elsif nTam.CompareTo(nUmTera) == 1 and nTam.CompareTo(nUmPeta) == -1 then
				nTamLocal = nTam / nUmTera
				return VisitFoldersUtil.FormatDecimal(nTamLocal) + " TByte(s)"
			else
				nTamLocal = nTam / nUmPeta
				return VisitFoldersUtil.FormatDecimal(nTamLocal) + " PByte(s)"
			end
		end

		def VisitFoldersUtil.attributesToPreFile(dir)
			pf = PreFile.new()
			sAtributos = ""
			sName = dir.Name.Replace("'", "''")
			pf.setName(sName)
			pf.setSize(0)
			pf.setModified(dir.LastWriteTime)
			sAtributos += "[DIR]"
			if dir.Attributes == FileAttributes.Hidden then
				sAtributos += "[HID]"
			end
			if dir.Attributes == FileAttributes.System then
				sAtributos += "[SYS]"
			end
			pf.setAttributes(sAtributos)
			pf.setOriginalPath(dir.FullName)
			pf.setDirectory(true)
			pf.setFormatedSize(VisitFoldersUtil.MountBigSize(pf.getSize()))
			pf.setFormatedModified(pf.getModified().ToString("dd/MM/yyyy hh:mm:ss"))
			return pf
		end

		def VisitFoldersUtil.attributesToPreFile(file)
			pf = PreFile.new()
			sAtributos = ""
			sName = file.Name.Replace("'", "''")
			pf.setName(sName)
			pf.setSize(file.Length)
			pf.setModified(file.LastWriteTime)
			sAtributos += "[ARQ]"
			if file.IsReadOnly then
				sAtributos += "[ROL]"
			end
			if file.Attributes == FileAttributes.Hidden then
				sAtributos += "[HID]"
			end
			if file.Attributes == FileAttributes.System then
				sAtributos += "[SYS]"
			end
			pf.setAttributes(sAtributos)
			pf.setOriginalPath(file.FullName)
			pf.setDirectory(false)
			pf.setFormatedSize(VisitFoldersUtil.MountBigSize(pf.getSize()))
			pf.setFormatedModified(pf.getModified().ToString("dd/MM/yyyy hh:mm:ss"))
			return pf
		end

		def VisitFoldersUtil.TraverseDirs(lst, dir)
			begin
				enumerator = dir.GetDirectories().GetEnumerator()
				while enumerator.MoveNext()
					iInfo = enumerator.Current
					#if (iInfo.Name.EndsWith(fileSufix)){
					lst.Add(VisitFoldersUtil.attributesToPreFile(iInfo))
					#}
					VisitFoldersUtil.TraverseDirs(lst, iInfo)
				end
			rescue Exception => 
			ensure
			end
			begin
				enumerator = dir.GetFiles().GetEnumerator()
				while enumerator.MoveNext()
					iInfo = enumerator.Current
					#if (iInfo.Name.EndsWith(fileSufix)){
					lst.Add(VisitFoldersUtil.attributesToPreFile(iInfo))
				end
			rescue Exception => 
				#}
			ensure
			end
		end
	end
end