#ifndef CONSOLE_DEFINED
#define	CONSOLE_DEFINED

#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <limits>

enum Error
{
	SendError,
	RecvError,
	OpponentQuit,
	StartupError,
	NoError
} ;

class CConsole
{
	public:
	static void Print(const char *pFmt, ...);
	static void PrintError(Error Error);

	static void GetInteger(int *pRet);
	static void GetUnsigned(unsigned *pRet);
	static void GetString(char *pStr);
} ;

#endif

