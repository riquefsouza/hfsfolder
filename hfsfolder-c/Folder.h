#ifndef Folder_H
#define Folder_H

/*
 * @author Henrique Figueiredo de Souza
 * @version 1.0
 * @since 2019
 */

struct SFolder {
    PreFile preFile;
	int code;
	int order;
	int parentCodFolder;
	char folderType;
	String path;
	String parentName;
	String parentPath;
	String originalPath;
};

typedef struct SFolder Folder;

void Folder_limparDados();


#endif // Folder_H
