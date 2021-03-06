#ifndef GUI_DEFINED
#define GUI_DEFINED

#include <cstdarg>
#ifdef _WIN32
	#include <curses.h>
	#undef CreateWindow
#else
	#include <ncurses.h>
#endif

enum
{
	Standout,
	Underline,
	Reverse,
	Blink,
	Dim,
	Bold,
	Invisible
};

class CWindow
{
public:
	CWindow(unsigned int Height, unsigned int Width, unsigned int y, unsigned int x);
	~CWindow();
	//CWindow(const &CWindow Window);
	CWindow(WINDOW *pWindow);
	void Print(const char *pFmt, ...);
	void MovePrint(unsigned int y, unsigned int x, const char *pFmt, ...);
	void Move(unsigned int y, unsigned int x);
	int GetCh();
	int GetInt();
	void GetString(char *pString);
	unsigned int GetMaxY();
	unsigned int GetMaxX();
	void ActivateAttribute(int Attribute);
	void DeactivateAttribute(int Attribute);
	void SetForegroundColor(int Color);
	void SetBackgroundColor(int Color);
	void Update();
	void Clear();

private:
	WINDOW *m_pWindow;
	int m_CurrentForegroundColor;
	int m_CurrentBackgroundColor;
};

class CGui
{
public:
	CGui();
	~CGui();
	CWindow * CreateWindow(unsigned int Height, unsigned int Width, unsigned int y, unsigned int x);
	CWindow * GetMainWindow();
	unsigned int GetMaxY();
	unsigned int GetMaxX();
	void Clear();
private:
	CWindow *m_pMainWindow;
};

extern CGui * CreateGui();

#endif