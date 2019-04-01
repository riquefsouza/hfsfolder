#include "Folder.h"
#include <iostream>

using namespace std;

namespace hfsfolder_model
{
	
Folder::Folder()
{
	this->limparDados();
}

Folder::~Folder()
{
}

Folder::Folder(PreFile preFile) {
	this->limparDados();

	this->setName(preFile.getName());
	this->setSize(preFile.getSize());
	this->setModified(preFile.getModified());
	this->setAttributes(preFile.getAttributes());
	this->setFormatedSize(preFile.getFormatedSize());
	this->setFormatedModified(preFile.getFormatedModified());
	this->setOriginalPath(preFile.getOriginalPath());
	this->setDirectory(preFile.isDirectory());
}

void Folder::clone(Folder folder) {
	this->setName(folder.getName());
	this->setSize(folder.getSize());
	this->setModified(folder.getModified());
	this->setAttributes(folder.getAttributes());
	this->setFormatedSize(folder.getFormatedSize());
	this->setFormatedModified(folder.getFormatedModified());
	this->setOriginalPath(folder.getOriginalPath());
	this->setDirectory(folder.isDirectory());
	this->code = folder.getCode();
	this->order = folder.getOrder();
	this->parentCodFolder = folder.getParentCodFolder();
	this->folderType = folder.getFolderType();
	this->path = folder.getPath();
	this->parentName = folder.getParentName();
	this->parentPath = folder.getParentPath();
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

std::string Folder::toJSON() {
	std::stringstream ss;

	ss << "{\n  \"name\" : \"" << getName() << "\"," <<
		  "\n  \"size\" : " << getSize() << "," <<
		  "\n  \"modified\" : " << getModified() << "," <<
		  "\n  \"attributes\" : \"" << getAttributes() << "\"," <<
		  "\n  \"formatedSize\" : \"" << getFormatedSize() << "\"," <<
		  "\n  \"formatedModified\" : \"" << getFormatedModified() << "\"," <<
		  "\n  \"code\" : " << code << "," <<
		  "\n  \"order\" : " << order << "," <<
		  "\n  \"parentCodFolder\" : " << parentCodFolder << "," <<
		  "\n  \"folderType\" : \"" << folderType << "\"," <<
		  "\n  \"path\" : \"" << path << "\"," <<
		  "\n  \"parentName\" : \"" << parentName << "\"," <<
		  "\n  \"parentPath\" : \"" << parentPath << "\"," <<
		  "\n  \"originalPath\" : \"" << getOriginalPath() << "\"\n}";

	return ss.str();
}

bool Folder::compareTo(Folder &folder1, Folder &folder2)
{
	return (folder1.getPath() < folder2.getPath());
}

}
