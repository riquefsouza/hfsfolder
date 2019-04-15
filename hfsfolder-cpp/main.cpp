#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include "VisitFoldersUtil.h"
#include "ProcessFolders.h"
#include "PreFile.h"

using namespace std;
using namespace boost::algorithm;
using namespace hfsfolder;
using namespace hfsfolder_util;
using namespace hfsfolder_model;

int main(int argc, char *argv[])
{
	std::string folder = "", opt = "";
	bool tojson = false, tofile = false, toinsert = false, tocvs = false;

	if (argc > 1) {
		
		for (int i = 1; i < argc; i++) {
			opt = argv[i];

			if (!contains(opt, "--")) {
				folder = opt;
			}
			if (contains(opt, "--version")) {
				std::cout << "hfsfolder 1.0" << std::endl;
			}
			if (contains(opt, "--tojson")) {
				tojson = true;
			}
			if (contains(opt, "--tofile")) {
				tofile = true;
			}
			if (contains(opt, "--toinsert")) {
				toinsert = true;
			}
			if (contains(opt, "--tocvs")) {
				tocvs = true;
			}
		}

		if (folder.size() > 0) {
			std::string data = "", outFile = "hfsfolder";
			if (tojson) {
				outFile += ".json";
				data = ProcessFolders::processFoldersToJson(folder);
			}
			if (toinsert) {
				std::cout << "Inform tab number: ";
				int naba;
				std::cin >> naba;
				outFile += "-insert.sql";
				data = ProcessFolders::processFoldersToInsert(folder, naba);
			}
			if (tocvs) {
				outFile += ".csv";
				data = ProcessFolders::processFoldersToCSV(folder);
			}

			if (tofile && data.size() > 0) {
				ProcessFolders::processFoldersToFile(data, outFile);
				std::cout << "Finish process folders!" << std::endl;
			}
			else if (data.size() > 0) {
				std::cout << data << std::endl;
			}

			if (!tojson && !toinsert && !tocvs && !tofile) {
				std::cout << "Inform option!" << std::endl;
			}
		}
		else {
			if (tojson || toinsert || tocvs || tofile) {
				std::cout << "Inform folder!" << std::endl;
			}
		}
	}
	else {
		std::cout << "HFSFolder\n" \
			"Usage:\n" \
			"    hfsfolder-cpp /folder\n\n" \
			"Options:\n" \
			"    --version\n" \
			"    --tojson\n" \
			"    --toinsert\n" \
			"    --tocvs\n" \
			"    --tofile\n\n" \
			"Example:\n" \
			"    hfsfolder-cpp /folder --tojson --tofile --version\n" << std::endl;
	}

	return 0;
}

