#ifndef ProcessFolder_H
#define ProcessFolder_H

#pragma once

#include "StringUtil.h"
#include "Folder.h"
#include "FolderList.h"
#include "FolderOrder.h"
#include "StringList.h"

String ProcessFolders_MountBigSize(long double nTam);
String ProcessFolders_MountSize(long long nTam);

PreFile ProcessFolders_attributesToPreFile(Folder folder);
Folder ProcessFolders_createFolder(Folder sfile, FolderOrder *folderOrder);
bool ProcessFolders_filterFindFirst(FolderList listFolders, String sfolder, Folder *rfolder);
FolderList ProcessFolders_process(String folder);

StringList ProcessFolders_processFoldersToJson(String folder);
void ProcessFolders_processFoldersToFile(StringList data, const String sfile);
StringList ProcessFolders_processFoldersToInsert(String folder, int naba);
StringList ProcessFolders_processFoldersToCSV(String folder);

#endif
