#ifndef ProcessFolder_H
#define ProcessFolder_H

#pragma once

#include "StringUtil.h"
#include "Folder.h"
#include "FolderList.h"
#include "FolderOrder.h"

String ProcessFolders_MountBigSize(long double nTam);
String ProcessFolders_MountSize(long long nTam);

PreFile ProcessFolders_attributesToPreFile(Folder sfile);
Folder ProcessFolders_createFolder(Folder sfile, FolderOrder *folderOrder);
bool ProcessFolders_filterFindFirst(FolderList listFolders, String sfolder, Folder *rfolder);
FolderList ProcessFolders_process(String folder);

String ProcessFolders_processFoldersToJson(String folder);
void ProcessFolders_processFoldersToFile(String data, const String sfile);
String ProcessFolders_processFoldersToInsert(String folder, int naba);
String ProcessFolders_processFoldersToCSV(String folder);

#endif
