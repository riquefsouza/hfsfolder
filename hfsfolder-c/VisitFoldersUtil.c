#include "VisitFoldersUtil.h"

#include "sys/types.h"
#include "sys/stat.h"
#include "unistd.h"
#include "errno.h"
#include "stdio.h"

#include "PreFile.h"
#include "Folder.h"

Folder VisitFoldersUtil_attributesToPreFile(char *dname, char *fn, struct stat st)
{
	Folder folder;
	String sAtributos = String_limpar();
	String sName = String_limpar();
	
	Folder_limparDados(folder);
	
	sName = String_copiar1(dname);
	sName = String_ReplaceAll(sName, "'", "''");
	folder.preFile.name = String_copiar4(sName);
	folder.preFile.size = st.st_size;
	
	folder.preFile.originalPath = String_iniciar2(fn);

	if ((st.st_mode & S_IFMT) == S_IFDIR) {
		sAtributos = String_concatenar4(sAtributos, "[DIR]");
		folder.preFile.modified = DateTime_raw(st.st_ctime);
		folder.preFile.directory = true;
	}
	else {
		sAtributos = String_concatenar4(sAtributos, "[ARQ]");
		folder.preFile.modified = DateTime_raw(st.st_mtime);
		folder.preFile.directory = false;
	}

	//S_IREAD S_IWRITE
	/*
	if ((st.st_mode & S_IFMT) != S_IWUSR) {
		sAtributos = String_concatenar4(sAtributos, "[ROL]");
	}
	 */
	folder.preFile.attributes = String_copiar4(sAtributos);
	
	return folder;
}

int VisitFoldersUtil_walk_recur(char *dname, regex_t *reg, int spec, FolderList *lfolder, int *index)
{
	
	
    struct dirent *dent;
    DIR *dir;
    struct stat st;
    char fn[FILENAME_MAX];
    int res = WALK_OK;
    int len = strlen(dname);
    if (len >= FILENAME_MAX - 1)
        return WALK_NAMETOOLONG;
    strcpy(fn, dname);
    fn[len++] = '/';
    if (!(dir = opendir(dname)))
    {
        printf("can't open %s", dname);
        return WALK_BADIO;
    }
    errno = 0;
    while ((dent = readdir(dir)))
    {
        if (!(spec & WS_DOTFILES) && dent->d_name[0] == '.')
            continue;
        if (!strcmp(dent->d_name, ".") || !strcmp(dent->d_name, ".."))
            continue;
        strncpy(fn + len, dent->d_name, FILENAME_MAX - len);

        #ifdef __WIN32__
            if( stat( fn, &st ) == -1 ){
                printf("Can't stat %s", fn);
                res = WALK_BADIO;
                continue;
            }
        #else
            if (lstat(fn, &st) == -1){
                printf("Can't stat %s", fn);
                res = WALK_BADIO;
                continue;
            }

            if (S_ISLNK(st.st_mode) && !(spec & WS_FOLLOWLINK))
                continue;
        #endif


        if (S_ISDIR(st.st_mode))
        {

            if ((spec & WS_RECURSIVE)){
                VisitFoldersUtil_walk_recur(fn, reg, spec, lfolder, index);
            }
            if (!(spec & WS_MATCHDIRS))
                continue;
        }

        if (!regexec(reg, fn, 0, 0, 0)) {
			Folder folder = VisitFoldersUtil_attributesToPreFile(dent->d_name, fn, st);
			FolderList_insereFim(lfolder, folder);
        }
    }
    if (dir)
        closedir(dir);
    return res ? res : errno ? WALK_BADIO : WALK_OK;

}

int VisitFoldersUtil_walk_dir(char *dname, char *pattern, int spec, FolderList *lfolder, int *index)
{
    regex_t r;
    int res;
    if (regcomp(&r, pattern, REG_EXTENDED | REG_NOSUB))
        return WALK_BADPATTERN;
    res = VisitFoldersUtil_walk_recur(dname, &r, spec, lfolder, index);
    regfree(&r);
    return res;
}

FolderList VisitFoldersUtil_process(char *folder)
{
	FolderList lfolder = FolderList_inicia();

	//Folder folder = VisitFoldersUtil_attributesToPreFile(folder, fn);
	//FolderList_insereFim(lfolder, folder);	
	
    int index = 0;
    int r = VisitFoldersUtil_walk_dir(folder, "$", WS_DEFAULT|WS_MATCHDIRS, &lfolder, &index);
    switch(r)
    {
    case WALK_OK:
        break;
    case WALK_BADIO:
        printf("IO error");
    case WALK_BADPATTERN:
        printf("Bad pattern");
    case WALK_NAMETOOLONG:
        printf("Filename too long");
    default:
        printf("Unknown error?");
    }
	
	return lfolder;
}

