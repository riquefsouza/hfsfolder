#include "PreFile.h"

namespace hfsfolder_model
{

PreFile::PreFile()
{
}

PreFile::PreFile(std::string name, unsigned long long size, ptime modified, 
	std::string attributes, std::string formatSize, std::string formatModified) {
	this->name = name;
	this->size = size;
	this->modified = modified;
	this->attributes = attributes;
	this->formatedSize = formatSize;
	this->formatedModified = formatModified;
}
	
PreFile::~PreFile()
{
}

std::string PreFile::getName()
{
	return name;
}

void PreFile::setName(std::string name)
{
	this->name = name;
}

unsigned long long PreFile::getSize()
{
	return size;
}

void PreFile::setSize(unsigned long long size)
{
	this->size = size;
}

ptime PreFile::getModified()
{
	return modified;
}

void PreFile::setModified(ptime modified)
{
	this->modified = modified;
}

std::string PreFile::getAttributes()
{
	return attributes;
}

void PreFile::setAttributes(std::string attributes)
{
	this->attributes = attributes;
}

std::string PreFile::getFormatedSize()
{
	return formatedSize;
}

void PreFile::setFormatedSize(std::string formatedSize)
{
	this->formatedSize = formatedSize;
}

std::string PreFile::getFormatedModified()
{
	return formatedModified;
}

void PreFile::setFormatedModified(std::string formatedModified)
{
	this->formatedModified = formatedModified;
}

std::string PreFile::getOriginalPath() {
	return originalPath;
}

void PreFile::setOriginalPath(std::string originalPath) {
	this->originalPath = originalPath;
}

void PreFile::setDirectory(bool directory){
	this->directory = directory;
}

bool PreFile::isDirectory(){
	return directory;
}
	
void PreFile::limparDados() {
	this->name = "";
	this->size = 0;
	this->modified = second_clock::local_time();
	this->attributes = "";
	this->formatedSize = "";
	this->formatedModified = "";	
	this->originalPath = "";
}

std::string PreFile::toString() {
	std::stringstream ss;
	ss << "PreFile [name=" << name << ", size=" << size << ", modified=" << to_simple_string(modified) 
		<< ", attributes=" << attributes << ", formatSize=" << formatedSize 
		<< ", formatModified=" << formatedModified << "]";
	return ss.str();
}

std::string PreFile::toInsert() {
	std::stringstream ss;
	ss << "'" << getName() << "'," << size << ",'" << formatedModified << "','" << attributes << "'";
	return ss.str();
}

std::string PreFile::toCVS() {
	std::stringstream ss;
	ss << getName() << ";" << size << ";" << formatedModified << ";" << attributes;
	return ss.str();
}
	
} // namespace model