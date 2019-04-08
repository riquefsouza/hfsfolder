/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 08/04/2019
 * Time: 12:20
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Linq;

namespace hfsfolder
{
	class Program
	{
		public static void Main(string[] args)
		{
			string folder = "";
			bool tojson = false, tofile = false, toinsert = false, tocvs = false;
	
			if (args.Length > 0) {
	
				foreach (string opt in args) {
					if (!opt.Contains("--")) {
						folder = opt;
					}
					if (opt.Contains("--version")) {
						Console.WriteLine("hfsfolder 1.0");
					}
					if (opt.Contains("--tojson")) {
						tojson = true;
					}
					if (opt.Contains("--tofile")) {
						tofile = true;
					}
					if (opt.Contains("--toinsert")) {
						toinsert = true;
					}
					if (opt.Contains("--tocvs")) {
						tocvs = true;
					}
				}
	
				if (folder.Length > 0) {
					string data = "", outFile = "hfsfolder";
					if (tojson) {
						outFile += ".json";
						data = ProcessFolders.processFoldersToJson(folder);
					}
					if (toinsert) {
						Console.Write("Inform tab number: ");
						int naba = Convert.ToInt32(Console.ReadLine());
						outFile += "-insert.sql";
						data = ProcessFolders.processFoldersToInsert(folder, naba);
					}
					if (tocvs) {
						outFile += ".csv";
						data = ProcessFolders.processFoldersToCSV(folder);
					}
	
					if (tofile && data.Length > 0) {
						ProcessFolders.processFoldersToFile(data, outFile);
						Console.WriteLine("Finish process folders!");
					} else if (data.Length > 0) {
						Console.WriteLine(data);
					}
					
					if (!tojson && !toinsert && !tocvs && !tofile) {
						Console.WriteLine("Inform option!");
					}
				} else {
					if (tojson || toinsert || tocvs || tofile) {
						Console.WriteLine("Inform folder!");
					}
				}
			} else {
				Console.WriteLine("HFSFolder \n"
						+ "Usage:\n" 
						+ "    dotnet run /folder\n\n"
						+ "Options:\n"
						+ "    --version\n"
						+ "    --tojson\n"
						+ "    --toinsert\n" 
						+ "    --tocvs\n" 
						+ "    --tofile\n\n" 
						+ "Example:\n"
						+ "    dotnet run /folder --tojson --tofile --version\n");
			}
			
		}
	}
}