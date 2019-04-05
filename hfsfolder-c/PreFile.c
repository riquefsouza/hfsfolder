#include "PreFile.h"

PreFile* PreFile_new() {
	PreFile *preFile;
	preFile = (PreFile*)malloc(sizeof(struct SPreFile));

	return(preFile);
}

PreFile PreFile_copy(PreFile preFile) {
	PreFile lpreFile;

	lpreFile.name = String_copiar4(preFile.name);
	lpreFile.size = preFile.size;
	lpreFile.modified = DateTime_copiar(preFile.modified);
	lpreFile.attributes = String_copiar4(preFile.attributes);
	lpreFile.formatedSize = String_copiar4(preFile.formatedSize);
	lpreFile.formatedModified = String_copiar4(preFile.formatedModified);
	lpreFile.originalPath = String_copiar4(preFile.originalPath);
	lpreFile.directory = preFile.directory;
	
	return lpreFile;
}

bool PreFile_compare(PreFile preFile1, PreFile preFile2) {
	return (		
	String_comparar1(preFile1.name, preFile2.name)
	&& preFile1.size == preFile2.size
	&& DateTime_comparar(preFile1.modified, preFile2.modified)
	&& String_comparar1(preFile1.attributes, preFile2.attributes)
	&& String_comparar1(preFile1.formatedSize, preFile2.formatedSize)
	&& String_comparar1(preFile1.formatedModified, preFile2.formatedModified)
	&& String_comparar1(preFile1.originalPath, preFile2.originalPath)
	&& preFile1.directory == preFile2.directory
	);
}

void PreFile_limparDados(PreFile preFile) {
	preFile.name = String_limpar();
	preFile.size = 0;
	preFile.modified = DateTime_Now();
	preFile.attributes = String_limpar();
	preFile.formatedSize = String_limpar();
	preFile.formatedModified = String_limpar();
	preFile.originalPath = String_limpar();
	preFile.directory = false;	
}

