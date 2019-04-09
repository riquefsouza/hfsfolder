#include "stdio.h"
#include "Folder.h"
#include "FolderList.h"
#include "VisitFoldersUtil.h"
#include "ProcessFolders.h"

int main(int argc, char *argv[])
{
	String folder = String_limpar();
	String opt = String_limpar();
	bool tojson = false, tofile = false, toinsert = false, tocvs = false;

	if (argc > 1) {
		
		for (int i = 1; i < argc; i++) {
			opt = String_copiar1(argv[i]);

			if (!String_cContainsStr(opt.str, "--")) {
				folder = String_copiar4(opt);
			}
			if (String_cContainsStr(opt.str, "--version")) {
				printf("hfsfolder 1.0\n");
			}
			if (String_cContainsStr(opt.str, "--tojson")) {
				tojson = true;
			}
			if (String_cContainsStr(opt.str, "--tofile")) {
				tofile = true;
			}
			if (String_cContainsStr(opt.str, "--toinsert")) {
				toinsert = true;
			}
			if (String_cContainsStr(opt.str, "--tocvs")) {
				tocvs = true;
			}
		}

		if (folder.length > 0) {
			StringList data;
			StringList local;
			String outFile = String_iniciar2("hfsfolder");
			if (tojson) {
				outFile = String_concatenar4(outFile, ".json");
				data = ProcessFolders_processFoldersToJson(folder);
			}
			if (toinsert) {
				printf("Inform tab number: ");
				int naba;
				scanf("%d", &naba);
				outFile = String_concatenar4(outFile, "-insert.sql");
				data = ProcessFolders_processFoldersToInsert(folder, naba);
			}
			if (tocvs) {
				outFile = String_concatenar4(outFile, ".csv");
				data = ProcessFolders_processFoldersToCSV(folder);
			}

			if (tofile && StringList_conta(data) > 0) {
				ProcessFolders_processFoldersToFile(data, outFile);
				printf("Finish process folders!\n");
			}
			else if (StringList_conta(data) > 0) {
				for (local = data; local != NULL; local = local->next) {
					printf(local->str.str);
				}
			}

			if (!tojson && !toinsert && !tocvs && !tofile) {
				printf("Inform option!\n");
			}
		}
		else {
			if (tojson || toinsert || tocvs || tofile) {
				printf("Inform folder!\n");
			}
		}
	}
	else {
		printf("HFSFolder\n" \
			"Usage:\n" \
			"    java -jar hfsfolder-java.jar /folder\n\n" \
			"Options:\n" \
			"    --version\n" \
			"    --tojson\n" \
			"    --toinsert\n" \
			"    --tocvs\n" \
			"    --tofile\n\n" \
			"Example:\n" \
			"    java -jar hfsfolder-java.jar /folder --tojson --tofile --version\n\n");
	}

    return 0;
}
