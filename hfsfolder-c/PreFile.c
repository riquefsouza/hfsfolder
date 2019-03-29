#include <PreFile.h>

void PreFile_limparDados(PreFile preFile) {
strcpy(preFile.name, "");
preFile.size = 0;
preFile.modified = Calendar.getInstance();
preFile.attributes = "";
preFile.formatedSize = "";
preFile.formatedModified = "";
}

