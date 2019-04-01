#ifndef ProcessFolder_H
#define ProcessFolder_H
#pragma once
#include "stdafx.h"

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

int ProcessFolders_walk_recur(char *dname, regex_t *reg, int spec, FolderList *lfolder, int *index);
int ProcessFolders_walk_dir(char *dname, char *pattern, int spec, FolderList *lfolder, int *index);
void ProcessFolders_process(char *folder, FolderList *lfolder);

#endif
