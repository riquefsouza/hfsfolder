using System;
using System.IO;

namespace hfsfolder_csharp
{
    class Program
    {

        static void Main(string[] args)
        {
            DirectoryInfo tDir = new DirectoryInfo(@"C:\temp");
            string Pattern = "dump";
            TraverseDirs(tDir, Pattern);
            Console.Read();
        }
        private static void TraverseDirs(DirectoryInfo dir, string Pattern)
        {
            try
            {
                foreach (DirectoryInfo iInfo in dir.GetDirectories())
                {
                    if (iInfo.Name.StartsWith(Pattern))
                        Console.WriteLine("Found dir: " + iInfo.FullName);
                    TraverseDirs(iInfo, Pattern);
                }
            }
            catch (Exception)
            {
                Console.Error(e.Message);
            }

            try 
            {
                foreach (FileInfo iInfo in dir.GetFiles())
                {
                    if (iInfo.Name.StartsWith(Pattern))
                        Console.WriteLine("Found file: " + iInfo.FullName);
                }
            }
            catch (Exception e)
            {
                Console.Error(e.Message);
            }

        }
    }
}
