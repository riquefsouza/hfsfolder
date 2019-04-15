# 
# * Created by SharpDevelop.
# * User: henrique.souza
# * Date: 08/04/2019
# * Time: 12:20
# *
# * To change this template use Tools | Options | Coding | Edit Standard Headers.
# 
require "mscorlib"
require "System, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a"
require "System.Linq, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a"

module hfsfolder
	class Program
		def Program.Main(args)
			folder = ""
			tojson = false
			tofile = false
			toinsert = false
			tocvs = false
			if args.Length > 0 then
				enumerator = args.GetEnumerator()
				while enumerator.MoveNext()
					opt = enumerator.Current
					if not opt.Contains("--") then
						folder = opt
					end
					if opt.Contains("--version") then
						Console.WriteLine("hfsfolder 1.0")
					end
					if opt.Contains("--tojson") then
						tojson = true
					end
					if opt.Contains("--tofile") then
						tofile = true
					end
					if opt.Contains("--toinsert") then
						toinsert = true
					end
					if opt.Contains("--tocvs") then
						tocvs = true
					end
				end
				if folder.Length > 0 then
					data = ""
					outFile = "hfsfolder"
					if tojson then
						outFile += ".json"
						data = ProcessFolders.processFoldersToJson(folder)
					end
					if toinsert then
						Console.Write("Inform tab number: ")
						naba = Convert.ToInt32(Console.ReadLine())
						outFile += "-insert.sql"
						data = ProcessFolders.processFoldersToInsert(folder, naba)
					end
					if tocvs then
						outFile += ".csv"
						data = ProcessFolders.processFoldersToCSV(folder)
					end
					if tofile and data.Length > 0 then
						ProcessFolders.processFoldersToFile(data, outFile)
						Console.WriteLine("Finish process folders!")
					elsif data.Length > 0 then
						Console.WriteLine(data)
					end
					if not tojson and not toinsert and not tocvs and not tofile then
						Console.WriteLine("Inform option!")
					end
				else
					if tojson or toinsert or tocvs or tofile then
						Console.WriteLine("Inform folder!")
					end
				end
			else
				Console.WriteLine("HFSFolder \n" + "Usage:\n" + "    hfsfolder-ironruby /folder\n\n" + 
				"Options:\n" + "    --version\n" + "    --tojson\n" + "    --toinsert\n" + 
				"    --tocvs\n" + "    --tofile\n\n" + "Example:\n" + 
				"    hfsfolder-ironruby /folder --tojson --tofile --version\n")
			end
		end
	end
end

Program.Main(nil)