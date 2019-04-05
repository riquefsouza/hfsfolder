#ifndef PreFile_H
#define PreFile_H

#pragma once

#include "StringUtil.h"
#include "DateTime.h"

struct SPreFile {
    String name;
	unsigned long long size;
	DateTime modified;
    String attributes;
    String formatedSize;
    String formatedModified;
	String originalPath;
	bool directory;
	char separatorChar;
};

typedef struct SPreFile PreFile;

PreFile* PreFile_new();
PreFile PreFile_copy(PreFile preFile);
bool PreFile_compare(PreFile preFile1, PreFile preFile2);

void PreFile_limparDados(PreFile preFile);

#endif
