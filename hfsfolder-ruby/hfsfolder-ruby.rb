#!/usr/bin/ruby -w
require_relative 'ProcessFolders'

def main
  processFolders = ProcessFolders.new
  folder = ""
  tojson = false
  tofile = false
  toinsert = false
  tocvs = false

  if ARGV.length > 0

    ARGV.each {|opt|
      unless opt.include?("--")
        folder = opt
      end
      if opt.include?("--version")
        puts "hfsfolder 1.0"
      end
      if opt.include?("--tojson")
        tojson = true
      end
      if opt.include?("--tofile")
        tofile = true
      end
      if opt.include?("--toinsert")
        toinsert = true
      end
      if opt.include?("--tocvs")
        tocvs = true
      end
    }

    if folder.length > 0
      data = ""
      outFile = File.expand_path(File.dirname(__FILE__)) + "/hfsfolder"
      if tojson
        outFile += ".json"
        data = processFolders.processFoldersToJson(folder)
      end
      if toinsert
        puts "Inform tab number: "
        saba = $stdin.gets
        saba = saba.chop!
        naba = saba.to_i
        outFile += "-insert.sql"
        data = processFolders.processFoldersToInsert(folder, naba)
      end
      if tocvs
        outFile += ".csv"
        data = processFolders.processFoldersToCSV(folder)
      end
      if tofile and data.length > 0
        processFolders.processFoldersToFile(data, outFile)
        puts "Finish process folders!"
      elsif data.length > 0
        puts data
      end
      if not tojson and not toinsert and not tocvs and not tofile
          puts "Inform option!"
      end
    else
      if tojson or toinsert or tocvs or tofile
        puts "Inform folder!"
      end
    end

  else
    puts "HFSFolder
Usage:
    ruby hfsfolder-ruby.rb /folder\n
Options:
    --version
    --tojson
    --toinsert
    --tocvs
    --tofile

Example:
    ruby hfsfolder-ruby.rb /folder --tojson --tofile --version"

  end

end

main
