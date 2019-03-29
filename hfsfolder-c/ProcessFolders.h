#ifndef ProcessFolder_H
#define ProcessFolder_H

/*
 * @author Henrique Figueiredo de Souza
 * @version 1.0
 * @since 2019
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
//#include <err.h>

#include <PreFile.h>

enum
{
    WALK_OK = 0,
    WALK_BADPATTERN,
    WALK_NAMETOOLONG,
    WALK_BADIO,
};

#define WS_NONE 0
#define WS_RECURSIVE (1 << 0)
#define WS_DEFAULT WS_RECURSIVE
#define WS_FOLLOWLINK (1 << 1) /* follow symlinks */
#define WS_DOTFILES (1 << 2) /* per unix convention, .file is hidden */
#define WS_MATCHDIRS (1 << 3) /* if pattern is used on dir names too */

int ProcessFolders_walk_recur(char *dname, regex_t *reg, int spec, ListPrefile *lpreFile, int *index);
int ProcessFolders_walk_dir(char *dname, char *pattern, int spec, ListPrefile *lpreFile, int *index);
void ProcessFolders_process(char *folder, ListPrefile *lpreFile);

#endif
