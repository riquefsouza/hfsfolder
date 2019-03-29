#include "Folder.h"

namespace hfsfolder_model
{
	
Folder::Folder()
{
}

Folder::~Folder()
{
}

Folder::Folder(PreFile *preFile) {
	PreFile(preFile->getName(), preFile->getSize(), preFile->getModified(), preFile->getAttributes(),
			preFile->getFormatedSize(), preFile->getFormatedModified());
}

int Folder::getCode() {
	return code;
}

void Folder::setCode(int code) {
	this->code = code;
}

int Folder::getOrder() {
	return order;
}

void Folder::setOrder(int order) {
	this->order = order;
}

int Folder::getParentCodFolder() {
	return parentCodFolder;
}

void Folder::setParentCodFolder(int parentCodFolder) {
	this->parentCodFolder = parentCodFolder;
}

char Folder::getFolderType() {
	return folderType;
}

void Folder::setFolderType(char folderType) {
	this->folderType = folderType;
}

std::string Folder::getPath() {
	return path;
}

void Folder::setPath(std::string path) {
	this->path = path;
}

std::string Folder::getParentName() {
	return parentName;
}

void Folder::setParentName(std::string parentName) {
	this->parentName = parentName;
}

std::string Folder::getParentPath() {
	return parentPath;
}

void Folder::setParentPath(std::string parentPath) {
	this->parentPath = parentPath;
}

void Folder::limparDados() {
	PreFile::limparDados();
	this->code = 0;
	this->order = 0;
	this->parentCodFolder = 0;
	this->folderType = 'A';
	this->path = "";
	this->parentName = "";
	this->parentPath = "";
}

std::string Folder::toString() {
	std::stringstream ss;
	ss << "Folder [codigo=" << code << ", ordem=" << order << ", codDirPai=" << parentCodFolder 
	<< ", tipo=" << folderType << ", caminho=" << path << ", nomePai=" << parentName 
	<< ", caminhoPai=" << parentPath << "]";
	return ss.str();
}

std::string Folder::toInsert(int naba) {
	std::stringstream ss;
	ss << "INSERT INTO Diretorios(aba, cod, ordem, nome, tam, tipo, modificado, atributos, coddirpai, caminho) VALUES("
			<< naba << "," << code << "," << order << ",'" << getName() << "'," << getSize() 
			<< ",'" << folderType << "','" << getFormatedModified() << "','" << getAttributes() 
			<< "'," << parentCodFolder << ",'" << getPath()	<< "');";
	return ss.str();		
}

std::string Folder::toCVS() {
	std::stringstream ss;
	ss << code << ";" << order << ";" << getName() << ";" << getSize() << ";" << folderType << ";" 
			<< getFormatedModified() << ";" << getAttributes() << ";" << parentCodFolder << ";" << getPath(); 
	return ss.str();		
}

}

