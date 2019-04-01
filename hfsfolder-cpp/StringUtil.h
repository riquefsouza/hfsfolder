#pragma once

#include <string>
#include <ctime>

using namespace std;

namespace hfsfolder_util
{

	class StringUtil
	{
	public:
		StringUtil();
		virtual ~StringUtil();

		static std::string LongLongToStr(const long long valor);
		static std::string LongDoubleToStr(const long double valor);
		/*
		static std::string replaceAll(const std::string texto,
			const std::string velho, const std::string novo);
		static bool startsWith(const std::string texto, const std::string subtexto);
		static int pos(const std::string subtexto, const std::string texto);
		static bool contains(const std::string texto, const std::string subtexto);
		*/
		static int lastIndexOf(const std::string texto, const char subtexto);
		static std::string FormatDateTime(struct tm InfoTempo);
	};

}