#ifndef PreFile_H
#define PreFile_H

#pragma once

#include "stdafx.h"

#include "StringUtil.h"
#include "DateTime.h"

struct SPrefile {
    String name;
	unsigned long long size;
	DateTime modified;
    String attributes;
    String formatedSize;
    String formatedModified;
	String originalPath;
	BOOL directory;
	char separatorChar;
};

typedef struct SPrefile PreFile;

void PreFile_limparDados(PreFile preFile);

#endif
