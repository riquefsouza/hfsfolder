#ifndef FolderOrder_H
#define FolderOrder_H

#pragma once

struct SFolderOrder {
    int codFolder;
    int order;
};

typedef struct SFolderOrder FolderOrder;

FolderOrder* FolderOrder_new();
FolderOrder* FolderOrder_new2(int codFolder, int order);

#endif
