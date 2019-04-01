#include "stdafx.h"

#include "PreFile.h"

void PreFile_limparDados(PreFile preFile) {
	preFile.name = String_limpar();
	preFile.size = 0;
	preFile.modified = DateTime_Now();
	preFile.attributes = String_limpar();
	preFile.formatedSize = String_limpar();
	preFile.formatedModified = String_limpar();
	preFile.originalPath = String_limpar();
	preFile.directory = FALSE;	
}

