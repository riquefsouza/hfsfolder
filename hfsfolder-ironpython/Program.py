# 
# * Created by SharpDevelop.
# * User: henrique.souza
# * Date: 08/04/2019
# * Time: 12:20
# *
# * To change this template use Tools | Options | Coding | Edit Standard Headers.
# 
from System import *
from System.Linq import *

class Program(object):
	def Main(args):
		folder = ""
		tojson = False
		tofile = False
		toinsert = False
		tocvs = False
		if args.Length > 0:
			enumerator = args.GetEnumerator()
			while enumerator.MoveNext():
				opt = enumerator.Current
				if not opt.Contains("--"):
					folder = opt
				if opt.Contains("--version"):
					Console.WriteLine("hfsfolder 1.0")
				if opt.Contains("--tojson"):
					tojson = True
				if opt.Contains("--tofile"):
					tofile = True
				if opt.Contains("--toinsert"):
					toinsert = True
				if opt.Contains("--tocvs"):
					tocvs = True
			if folder.Length > 0:
				data = ""
				outFile = "hfsfolder"
				if tojson:
					outFile += ".json"
					data = ProcessFolders.processFoldersToJson(folder)
				if toinsert:
					Console.Write("Inform tab number: ")
					naba = Convert.ToInt32(Console.ReadLine())
					outFile += "-insert.sql"
					data = ProcessFolders.processFoldersToInsert(folder, naba)
				if tocvs:
					outFile += ".csv"
					data = ProcessFolders.processFoldersToCSV(folder)
				if tofile and data.Length > 0:
					ProcessFolders.processFoldersToFile(data, outFile)
					Console.WriteLine("Finish process folders!")
				elif data.Length > 0:
					Console.WriteLine(data)
				if not tojson and not toinsert and not tocvs and not tofile:
					Console.WriteLine("Inform option!")
			else:
				if tojson or toinsert or tocvs or tofile:
					Console.WriteLine("Inform folder!")
		else:
			Console.WriteLine("HFSFolder \n" + "Usage:\n" + "    hfsfolder-ironpython /folder\n\n" + 
			"Options:\n" + "    --version\n" + "    --tojson\n" + "    --toinsert\n" + 
			"    --tocvs\n" + "    --tofile\n\n" + "Example:\n" + 
			"    hfsfolder-ironpython /folder --tojson --tofile --version\n")

	Main = staticmethod(Main)

Program.Main(None)