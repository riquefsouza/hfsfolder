#include <Folder.h>

/*
 * @author Henrique Figueiredo de Souza
 * @version 1.0
 * @since 2019
 */

void Folder_limparDados() {
    super.limparDados();
    this.code = 0;
    this.order = 0;
    this.parentCodFolder = 0;
    this.folderType = 'A';
    this.path = "";
    this.parentName = "";
    this.parentPath = "";
    this.originalPath = "";
}

@Override
public String toString() {
    return "Folder [codigo=" + code + ", ordem=" + order + ", codDirPai=" + parentCodFolder + ", tipo=" + folderType
            + ", caminho=" + path + ", nomePai=" + parentName + ", caminhoPai=" + parentPath + "]";
}

public String toInsert(int naba) {
    return "INSERT INTO Diretorios(aba, cod, ordem, nome, tam, tipo, modificado, atributos, coddirpai, caminho) VALUES("
            + naba + "," + code + "," + order + ",'" + getName() + "'," + getSize() + ",'" + folderType + "','"
            + getFormatedModified() + "','" + getAttributes() + "'," + parentCodFolder + ",'" + getPath()
            + "');";
}

public String toCVS() {
    return code + ";" + order + ";" + getName() + ";" + getSize() + ";" + folderType + ";"
            + getFormatedModified() + ";" + getAttributes() + ";" + parentCodFolder + ";" + getPath();
}

