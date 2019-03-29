#ifndef PreFile_H
#define PreFile_H

/*
 * @author Henrique Figueiredo de Souza
 * @version 1.0
 * @since 2019
 */




struct SPrefile {
    String name;
	long size;
	time_t modified;
    String attributes;
    String formatedSize;
    String formatedModified;
};

typedef struct SPrefile Prefile;

void Prefile_limparDados();

#endif
