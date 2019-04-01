#include "StringUtil.h"

#include <cstdlib>
#include <sstream>

namespace hfsfolder_util
{

	StringUtil::StringUtil()
	{
	}


	StringUtil::~StringUtil()
	{
	}

	std::string StringUtil::LongLongToStr(const long long valor) {
		char* retorno = new char[40];
		std::snprintf(retorno, 40, "%lld", valor);
		return retorno;

		/*
		std::stringstream ss;
		ss.precision(40);
		ss << valor;
		return ss.str();
		*/
	}

	std::string StringUtil::LongDoubleToStr(const long double valor) {
		char* retorno = new char[40];
		std::snprintf(retorno, 40, "%4.2Lf", valor);
		return retorno;

		/*
		std::stringstream ss;
		ss.precision(40);
		ss << valor;
		return ss.str();
		*/
	}
	/*
	std::string StringUtil::replaceAll(const std::string texto,
		const std::string velho, const std::string novo) {
		std::string stexto = texto;
		size_t pos = 0;
		while ((pos = stexto.find(velho, pos)) != std::string::npos)
		{
			stexto.replace(pos, velho.length(), novo);
			pos += novo.length();
		}
		return stexto;
	}

	bool StringUtil::startsWith(const std::string texto, const std::string subtexto) {
		return subtexto.length() <= texto.length()
			&& std::equal(subtexto.begin(), subtexto.end(), texto.begin());
	}

	int StringUtil::pos(const std::string subtexto, const std::string texto) {
		std::string::size_type loc = texto.find(subtexto, 0);
		if (loc != std::string::npos)
			return (loc + 1);
		else
			return -1;
	}

	bool StringUtil::contains(const std::string texto, const std::string subtexto) {
		return (pos(subtexto, texto) > 0);
	}
	*/
	int StringUtil::lastIndexOf(const std::string texto, const char subtexto) {
		std::string::size_type loc = texto.find_last_of(subtexto);
		if (loc != std::string::npos)
			return loc;
		else
			return -1;
	}
	

	std::string StringUtil::FormatDateTime(struct tm InfoTempo) {
		char tempo[20];
		std::stringstream retorno;

		tempo[0] = '\0';
		retorno << "";

		strftime(tempo, 20, "%d/%m/%Y %H:%M:%S", &InfoTempo);
		retorno << tempo;

		return retorno.str();
	}
}