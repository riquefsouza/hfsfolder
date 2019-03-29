#include <ProcessFolders.h>

/*
 * @author Henrique Figueiredo de Souza
 * @version 1.0
 * @since 2019
 */

int ProcessFolders_walk_recur(char *dname, regex_t *reg, int spec, ListPrefile *lpreFile, int *index)
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
            /* don't follow symlink unless told so */
            if (S_ISLNK(st.st_mode) && !(spec & WS_FOLLOWLINK))
                continue;
        #endif

        /* will be false for symlinked dirs */
        if (S_ISDIR(st.st_mode))
        {
            /* recursively follow dirs */
            if ((spec & WS_RECURSIVE)){
                ProcessFolders_walk_recur(fn, reg, spec, lpreFile, index);
            }
            if (!(spec & WS_MATCHDIRS))
                continue;
        }
        /* pattern match */
        if (!regexec(reg, fn, 0, 0, 0)) {
            //int fnlen = strlen(fn);

            strcpy(lpreFile[0]->name, fn);
            //lpreFile[count]->index = count;
            //lpreFile[count]->count = lpreFile[count]->index + 1;
            //puts(fn);
            index = (int)malloc(100);
            (*index)++;
            printf("%d\n", *index);

        }
    }
    if (dir)
        closedir(dir);
    return res ? res : errno ? WALK_BADIO : WALK_OK;

}

int ProcessFolders_walk_dir(char *dname, char *pattern, int spec, ListPrefile *lpreFile, int *index)
{
    regex_t r;
    int res;
    if (regcomp(&r, pattern, REG_EXTENDED | REG_NOSUB))
        return WALK_BADPATTERN;
    res = ProcessFolders_walk_recur(dname, &r, spec, lpreFile, index);
    regfree(&r);
    return res;
}

void ProcessFolders_process(char *folder, ListPrefile *lpreFile)
{
    int index = 0;
    int r = ProcessFolders_walk_dir(folder, "$", WS_DEFAULT|WS_MATCHDIRS, lpreFile, &index);
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
}
