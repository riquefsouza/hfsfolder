#pragma once
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

namespace hfsfolder_model
{

class PreFile
{
	private:
		std::string name;
		unsigned long long size;
		ptime modified;
		std::string attributes;
		std::string formatedSize;
		std::string formatedModified;
		std::string originalPath;
		bool directory;

	public:
		char separatorChar;
		
		PreFile();
		PreFile(std::string name, unsigned long long size, ptime modified, 
			std::string attributes, std::string formatSize, std::string formatModified);	
		virtual ~PreFile();

		std::string getName();
		void setName(std::string name);
		unsigned long long getSize();
		void setSize(unsigned long long size);
		ptime getModified();
		void setModified(ptime modified);
		std::string getAttributes();
		void setAttributes(std::string attributes);
		std::string getFormatedSize();
		void setFormatedSize(std::string formatedSize);
		std::string getFormatedModified();
		void setFormatedModified(std::string formatedModified);
		std::string getOriginalPath();
		void setOriginalPath(std::string originalPath);
		void setDirectory(bool directory);
		bool isDirectory();
		
		void limparDados();
		std::string toString();
		std::string toInsert();
		std::string toCVS();
	
};

} // namespace model
