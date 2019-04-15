#!/usr/bin/python
import sys
from ProcessFolders import ProcessFolders

def main():
    processFolders = ProcessFolders()
    folder = ""
    tojson = False
    tofile = False
    toinsert = False
    tocvs = False
    if len(sys.argv[1:]) > 0:
        for opt in sys.argv[1:]:
            if not opt.__contains__("--"):
                folder = opt
            if opt.__contains__("--version"):
                print("hfsfolder 1.0")
            if opt.__contains__("--tojson"):
                tojson = True
            if opt.__contains__("--tofile"):
                tofile = True
            if opt.__contains__("--toinsert"):
                toinsert = True
            if opt.__contains__("--tocvs"):
                tocvs = True
        if len(folder) > 0:
            data = ""
            outFile = "hfsfolder"
            if tojson:
                outFile += ".json"
                data = processFolders.processFoldersToJson(folder)
            if toinsert:
                naba = input("Inform tab number: ")
                naba = int(naba)
                outFile += "-insert.sql"
                data = processFolders.processFoldersToInsert(folder, naba)
            if tocvs:
                outFile += ".csv"
                data = processFolders.processFoldersToCSV(folder)
            if tofile and len(data) > 0:
                processFolders.processFoldersToFile(data, outFile)
                print("Finish process folders!")
            elif len(data) > 0:
                print(data)
            if not tojson and not toinsert and not tocvs and not tofile:
                print("Inform option!")
        else:
            if tojson or toinsert or tocvs or tofile:
                print("Inform folder!")
    else:
        print("HFSFolder \n" \
              + "Usage:\n" \
              + "    python hfsfolder_python.py /folder\n\n" \
              + "Options:\n" \
              + "    --version\n" \
              + "    --tojson\n" \
              + "    --toinsert\n" \
              + "    --tocvs\n" \
              + "    --tofile\n\n" \
              + "Example:\n" \
              + "    python hfsfolder_python.py /folder --tojson --tofile --version\n")

if __name__ == "__main__":
    main()


