#include "StringList.h"
#include "stdbool.h"
#include "String.h"
#include "malloc.h"
#include "string.h"

StringList StringList_aloca() 
{
	StringList ls;
	ls = (StringList)malloc(sizeof(struct noString));

	return(ls);
}

StringList StringList_inicia()
{
  return NULL;
}

void StringList_libera(StringList ls)
{
	free(ls);
}

void StringList_insereFim(StringList *ls, String str)
{
	StringList local, temp;

	local = StringList_aloca();
	local->order = 0;
	
	local->str = String_copiar4(str);
	
	local->next = NULL;
	if (*ls == NULL)
		*ls = local;
	else {
		/* procura o ulitmo no */
		for (temp = *ls; temp->next != NULL; temp = temp->next);
		local->order = temp->order;
		local->order++;
		temp->next = local;
	}
}

bool StringList_remove(StringList ls, String *str)
{
	StringList local;

	if ((ls == NULL) || (ls->next == NULL)) {
		// remoção nula
		return false;
	}
	local = ls->next;
	
	*str = String_copiar4(local->str);
	
	ls->next = local->next;
	StringList_libera(local);
	return true;
}

void StringList_arrumaOrdem(StringList ls)
{
StringList local;
unsigned int nordem;

  nordem = 0;
  for (local = ls; local != NULL; local = local->next) {
		local->order = nordem;
		nordem++;
  }
}

void StringList_removeItem(StringList *ls, String str, bool bArrumaOrdem)
{
	StringList local, temp;

	String localstr;
	temp = NULL;
	local = *ls;
	while (local != NULL) {
		if (String_comparar1(str, local->str)) {
			local = local->next;
			if (temp == NULL){
				/* remove o primeiro no da lista */
				StringList_libera(*ls);
				*ls = local;
			} else
				StringList_remove(temp, &localstr);
		} else {
			temp = local;
			local = local->next;
		}
	}
	if (bArrumaOrdem)
  	StringList_arrumaOrdem(*ls);
}

void StringList_removeItemOrd(StringList *ls, unsigned int ordem, bool bArrumaOrdem)
{
	StringList local, temp;

	String localstr;
	temp = NULL;
	local = *ls;
	while (local != NULL) {
		if (local->order == ordem){
			local = local->next;
			if (temp == NULL){
				/* remove o primeiro no da lista */
				StringList_libera(*ls);
				*ls = local;
			} else
				StringList_remove(temp, &localstr);
		} else {
			temp = local;
			local = local->next;
		}
	}
	if (bArrumaOrdem)
  	StringList_arrumaOrdem(*ls);
}

void StringList_removeTodos(StringList ls)
{ 
	int ncont, ntotal;
	ntotal = StringList_conta(ls);
	for (ncont=0; ncont < ntotal; ncont++)
		StringList_removeItemOrd(&ls, ncont, false);
}

bool StringList_pesquisaItem(StringList ls, String str)
{
	StringList local;

	for (local = ls; local != NULL; local = local->next) {
		if (String_comparar1(local->str, str))
			return true;
	}
	return false;
}

String StringList_pesquisaItemOrd(StringList ls, unsigned int ordem)
{
	StringList local;
	
	for (local = ls; local != NULL; local = local->next) {
		if (local->order == ordem)
			return local->str;
	}
	return String_limpar();
}

int StringList_conta(StringList ls)
{
	StringList local;
	int ncont;
	ncont = 0;
	for (local = ls; local != NULL; local = local->next)
		ncont++;

	return ncont;
}
