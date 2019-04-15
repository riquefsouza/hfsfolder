# 
# * User: henrique.souza
# * Date: 08/04/2019
# * Time: 14:09
#
require 'find'
require_relative '../model/PreFile'

class VisitFoldersUtil

  def getListFromFiles(folder)
    lst = []

    Find.find(folder) do |sfile|
      filename = File::basename(sfile)
      prefile = self.attributesToPreFile(sfile, filename)
      lst.push(prefile)
    end

    lst
  end

  #pattern = /\.*\Z/
  def getListFromFilesByPattern(folder, pattern)
    lst = []

    Find.find(folder) do |sfile|
      if filename.match(pattern)
        filename = File::basename(sfile)
        prefile = self.attributesToPreFile(sfile, filename)
        lst.push(prefile)
      end
    end

    lst
  end

  def formatDecimal(valor)
    "%.2f" % valor.to_f
  end

  def mountBigSize(nTam)
    nUmKilo = 1024
    nUmMega = nUmKilo * 1024
    nUmGiga = nUmMega * 1024
    nUmTera = nUmGiga * 1024
    nUmPeta = nUmTera * 1024

    if nTam < nUmKilo
      nTamLocal = nTam.to_f
      self.formatDecimal(nTamLocal) + " Byte(s)"
    elsif nTam > nUmKilo and nTam < nUmMega
      nTamLocal = nTam.to_f / nUmKilo
      return self.formatDecimal(nTamLocal) + " KByte(s)"
    elsif nTam > nUmMega and nTam < nUmGiga
      nTamLocal = nTam.to_f / nUmMega
      return self.formatDecimal(nTamLocal) + " MByte(s)"
    elsif nTam < nUmGiga and nTam > nUmTera
      nTamLocal = nTam.to_f / nUmGiga
      return self.formatDecimal(nTamLocal) + " GByte(s)"
    elsif nTam < nUmTera and nTam > nUmPeta
      nTamLocal = nTam.to_f / nUmTera
      return self.formatDecimal(nTamLocal) + " TByte(s)"
    else
      nTamLocal = nTam.to_f / nUmPeta
      self.formatDecimal(nTamLocal) + " PByte(s)"
    end
  end

  def attributesToPreFile(sfile, filename)
    pf = PreFile.new
    sAtributos = ""
    sName = filename.gsub("'", "''")
    pf.setName(sName)
    nsize = File::size?(sfile)
    pf.setSize(nsize == nil ? 0 : nsize)
    pf.setModified(File::mtime(sfile))

    unless File.writable?(sfile)
      sAtributos += "[ROL]"
    end

    if File::directory?(sfile)
        sAtributos += "[DIR]"
        pf.setDirectory(true)
    else
        sAtributos += "[ARQ]"
        pf.setDirectory(false)
    end

    pf.setAttributes(sAtributos)
    pf.setOriginalPath(sfile)
    pf.setFormatedSize(self.mountBigSize(pf.getSize))
    pf.setFormatedModified(pf.getModified.strftime("%d/%m/%Y %H:%M:%S"))
    pf
  end

end
