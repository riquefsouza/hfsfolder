#include <ProcessFolders.h>

/*
 * @author Henrique Figueiredo de Souza
 * @version 1.0
 * @since 2019
 */

int main()
{
    ListPrefile lpreFile;
    ProcessFolders_process("C:/ROMS-EMULS", &lpreFile);

    for(int i = 0; i < 10; i++){
        puts(lpreFile[i].name);
    }

    return 0;
}
