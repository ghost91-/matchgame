#include "console.h"

void CConsole::Print(const char *pFmt, ...)
{
	va_list Args;
	va_start(Args, pFmt);
	vprintf(pFmt, Args);
	va_end(Args);
}

void CConsole::PrintError(Error Error)
{
	switch(Error)
	{
		case SendError:
		Print("Failed to send data, maybe your opponent has quit the connection? Quitting the game!\n\n");
		break;

		case RecvError:
		Print("Failed to recieve data, quitting the game!\n\n");
		break;
		
		case OpponentQuit:
		Print("Your opponent quit the connection!\n\n");
		break;

		case StartupError:
		Print("Failed to startup. Abborting the game!\n\n");
		case NoError:
		break;
	}
	return;
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
