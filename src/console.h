#ifndef CONSOLE_DEFINED
#define	CONSOLE_DEFINED

#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <limits>

class CConsole
{
	public:
	static void Print(const char *pFmt, ...);

	static void GetInteger(int *pRet);
	static void GetUnsigned(unsigned *pRet);
	static void GetString(char *pStr);
} ;

#endif

