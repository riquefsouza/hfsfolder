package model

type Folder struct {
	preFile         PreFile
	code            int
	order           int
	parentCodFolder int
	folderType      string
	path            string
	parentName      string
	parentPath      string
	originalPath    string
}

func Folder_copiar(folder Folder) Folder {
	var lfolder Folder

	lfolder.preFile.name = folder.preFile.name
	lfolder.preFile.size = folder.preFile.size
	lfolder.preFile.modified = folder.preFile.modified
	lfolder.preFile.attributes = folder.preFile.attributes
	lfolder.preFile.formatedSize = folder.preFile.formatedSize
	lfolder.preFile.formatedModified = folder.preFile.formatedModified
	lfolder.preFile.originalPath = folder.preFile.originalPath
	lfolder.preFile.directory = folder.preFile.directory
	lfolder.code = folder.code
	lfolder.order = folder.order
	lfolder.parentCodFolder = folder.parentCodFolder
	lfolder.folderType = folder.folderType
	lfolder.path = folder.path
	lfolder.parentName = folder.parentName
	lfolder.parentPath = folder.parentPath

	return lfolder
}

func Folder_comparar(folder1 Folder, folder2 Folder) bool {
	return folder1.preFile.name == folder2.preFile.name && folder1.preFile.size == folder2.preFile.size
	/*
	   && folder1.preFile.modified == folder2.preFile.modified && folder1.preFile.attributes == folder2.preFile.attributes && folder1.preFile.formatedSize == folder2.preFile.formatedSize && folder1.preFile.formatedModified == folder2.preFile.formatedModified && folder1.preFile.originalPath == folder2.preFile.originalPath
	   && folder1.preFile.directory == folder2.preFile.directory
	   && folder1.code == folder2.code
	   && folder1.order == folder2.order
	   && folder1.parentCodFolder == folder2.parentCodFolder
	   && folder1.folderType == folder2.folderType
	   && folder1.path == folder2.path
	   && folder1.parentName == folder2.parentName
	   && folder1.parentPath == folder2.parentPath
	*/
}

func Folder_limparDados(folder Folder) {
	PreFile_limparDados(folder.preFile)
	folder.code = 0
	folder.order = 0
	folder.parentCodFolder = 0
	folder.folderType = "A"
	folder.path = ""
	folder.parentName = ""
	folder.parentPath = ""
	folder.originalPath = ""
}

func Folder_toString(folder Folder) string {
	str := "Folder [codigo=" + string(folder.code)
	str += ", ordem=" + string(folder.order)
	str += ", codDirPai=" + string(folder.parentCodFolder)
	str += ", tipo=" + folder.folderType
	str += ", caminho=" + folder.path
	str += ", nomePai=" + folder.parentName
	str += ", caminhoPai=" + folder.parentPath + "]";
	return str
}