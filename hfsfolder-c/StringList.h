#ifndef StringList_H
#define StringList_H

#pragma once

#include "stdbool.h"
#include "StringUtil.h"

struct noString {
	unsigned int order;
	String str;
	struct noString *next;
};
typedef struct noString *StringList;

StringList StringList_aloca();
StringList StringList_inicia();
void StringList_libera(StringList ls);
void StringList_insereFim(StringList *ls, String str);
bool StringList_remove(StringList ls, String *str);
void StringList_arrumaOrdem(StringList ls);
void StringList_removeItem(StringList *ls, String str, bool bArrumaOrdem);
void StringList_removeItemOrd(StringList *ls, unsigned int ordem, bool bArrumaOrdem);
void StringList_removeTodos(StringList ls);
bool StringList_pesquisaItem(StringList ls, String str);
String StringList_pesquisaItemOrd(StringList ls, unsigned int ordem);
int StringList_conta(StringList ls);

#endif
