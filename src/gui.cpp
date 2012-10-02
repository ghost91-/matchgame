#include "gui.h"
#include <cstdlib>
#ifdef _WIN32
	#include <curses.h>
#else
	#include <ncurses.h>
#endif

CWindow::CWindow(unsigned int Height, unsigned int Width, unsigned int y, unsigned int x)
{
	m_pWindow = newwin(Height, Width, y, x);
	keypad(m_pWindow, TRUE);
}

CWindow::CWindow(WINDOW *pWindow)
{
	m_pWindow = pWindow;
	keypad(m_pWindow, TRUE);
}

CWindow::~CWindow()
{
	Clear();
	Update();
	delwin(m_pWindow);
}

void CWindow::Print(const char *pFmt, ...)
{
	va_list Args;
	va_start(Args, *pFmt);
	vwprintw(m_pWindow, pFmt, Args);
	va_end(Args);
}

void CWindow::MovePrint(unsigned int y, unsigned int x, const char *pFmt, ...)
{
	va_list Args;
	va_start(Args, *pFmt);
	wmove(m_pWindow, y, x);
	vwprintw(m_pWindow, pFmt, Args);
	va_end(Args);
}

void CWindow::Move(unsigned int y, unsigned int x)
{
	wmove(m_pWindow, y, x);
}

int CWindow::GetCh()
{
	return wgetch(m_pWindow);
}

int CWindow::GetInt()
{
	char aBuf[16];
	echo();
	wgetstr(m_pWindow, aBuf);
	noecho();
	return strtol(aBuf, NULL, 10);
}

void CWindow::GetString(char *pString)
{
	echo();
	wgetstr(m_pWindow, pString);
	noecho();
}

unsigned int CWindow::GetMaxY()
{
	unsigned int y, x;
	getmaxyx(m_pWindow, y, x);
	return y;
}

unsigned int CWindow::GetMaxX()
{
	unsigned int y, x;
	getmaxyx(m_pWindow, y, x);
	return x;
}

void CWindow::ActivateAttribute(int Attribute)
{
	switch(Attribute)
	{
		case Standout:
		wattron(m_pWindow, A_STANDOUT);
		break;
		case Underline:
		wattron(m_pWindow, A_UNDERLINE);
		break;
		case Reverse:
		wattron(m_pWindow, A_REVERSE);
		break;
		case Blink:
		wattron(m_pWindow, A_BLINK);
		break;
		case Dim:
		wattron(m_pWindow, A_DIM);
		break;
		case Bold:
		wattron(m_pWindow, A_BOLD);
		break;
		case Invisible:
		wattron(m_pWindow, A_INVIS);
		break;
	}
}

void CWindow::DeactivateAttribute(int Attribute)
{
	switch(Attribute)
	{
		case Standout:
		wattroff(m_pWindow, A_STANDOUT);
		break;
		case Underline:
		wattroff(m_pWindow, A_UNDERLINE);
		break;
		case Reverse:
		wattroff(m_pWindow, A_REVERSE);
		break;
		case Blink:
		wattroff(m_pWindow, A_BLINK);
		break;
		case Dim:
		wattroff(m_pWindow, A_DIM);
		break;
		case Bold:
		wattroff(m_pWindow, A_BOLD);
		break;
		case Invisible:
		wattroff(m_pWindow, A_INVIS);
		break;
	}
}

void CWindow::Update()
{
	wrefresh(m_pWindow);
}

void CWindow::Clear()
{
	wclear(m_pWindow);
}

CGui::CGui()
{
	initscr();
	clear();
	noecho();
	cbreak();
	m_pMainWindow = new CWindow(stdscr);
}

CGui::~CGui()
{
	clrtoeol();
	refresh();
	endwin();
}

CWindow * CGui::CreateWindow(unsigned int Height, unsigned int Width, unsigned int y, unsigned int x)
{
	return new CWindow(Height, Width, y, x);
}

CWindow * CGui::GetMainWindow()
{
	return m_pMainWindow;
}

unsigned int CGui::GetMaxY()
{
	return m_pMainWindow->GetMaxY();
}

unsigned int CGui::GetMaxX()
{
	return m_pMainWindow->GetMaxX();
}

void CGui::Clear()
{
	clear();
}

CGui * CreateGui()
{
	return new CGui;
}

