#include "console.h"

void CConsole::Print(const char *pFmt, ...)
{
	va_list Args;
	va_start(Args, pFmt);
	std::vprintf(pFmt, Args);
	va_end(Args);
}
	
void CConsole::GetInteger(int *pRet)
{
	while (!(std::cin>>*pRet))
	{
		Print("Bad input! Enter a number: ");
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return;
}

void CConsole::GetUnsigned(unsigned *pRet)
{
	while (!(std::cin>>*pRet))
	{
		Print("Bad input! Enter a number: ");
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return;
}

void CConsole::GetString(char* pStr)
{
	std::cin>>pStr;
	return;
}
