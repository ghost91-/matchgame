#ifndef MENU_DEFINED
#define MENU_DEFINED

#include <vector>

#include <ncurses.h>

class IMenuEntry
{
protected:
	virtual void DoAction() = 0;
	virtual const char *DoGetName() const = 0;
	virtual const char *DoGetDescription() const { return ""; }

public:
	void Action() { DoAction(); }
	const char *GetName() const { return DoGetName(); }
	const char *GetDescription() const { return DoGetDescription(); }
	virtual ~IMenuEntry(){}
} ;

template<typename Class>
class CMenuEntryMethod : public IMenuEntry
{
private:
	Class *m_pObject;
	void (Class::*m_pMethod)();
	const char *m_pName;
  
protected:
	void DoAction()
	{
		(m_pObject->*m_pMethod)();
	}
	const char *DoGetName() const
	{
		return m_pName;
	}
 
public:
	CMenuEntryMethod(Class *pObject, void (Class::*pMethod)(), const char *pName)
	: m_pObject(pObject), m_pMethod(pMethod), m_pName(pName)
	{}
} ;

template<typename Class, typename Parameter>
class CMenuEntryMethodParameter : public IMenuEntry
{
private:
	Class *m_pObject;
	void (Class::*m_pMethod)(Parameter);
	Parameter m_Parameter;
	const char *m_pName;
  
protected:
	void DoAction()
	{
		(m_pObject->*m_pMethod)(m_Parameter);
	}
	const char *DoGetName() const
	{
		return m_pName;
	}
  
public:
	CMenuEntryMethodParameter(Class *pObject, void (Class::*pMethod)(Parameter), Parameter Param, const char *pName)
	: m_pObject(pObject), m_pMethod(pMethod), m_Parameter(Param), m_pName(pName)
	{}
} ;

template<typename Class>
CMenuEntryMethod<Class>* CreateMenuEntry(Class *pObject, void (Class::*pMethod)(), const char *pName)
{
	return new CMenuEntryMethod<Class>(pObject, pMethod, pName);
}

template<typename Class, typename Parameter>
CMenuEntryMethodParameter<Class, Parameter>* CreateMenuEntry(Class *pObject, void (Class::*pMethod)(Parameter), Parameter Param, const char *pName)
{
	return new CMenuEntryMethodParameter<Class, Parameter>(pObject, pMethod, Param, pName);
}

class IMenu
{
protected:
	std::vector<IMenuEntry*> m_Entries;
	/*virtual void DoDisplay() = 0;*/
	virtual void DoSelect() = 0;

public:
	virtual ~IMenu()
	{
		std::vector<IMenuEntry*>::iterator Iterator = m_Entries.begin();
		while(Iterator != m_Entries.end())
		{
			delete (*Iterator);
			++Iterator;
		}
	}
  
	void AddEntry(IMenuEntry* Entry)
	{
		m_Entries.push_back(Entry);
	}
  
	/*void Display() { DoDisplay(); }*/
	void Select() { DoSelect(); }
} ;

class CMenu : public IMenu
{
protected:
	/*void DoDisplay();*/
	void DoSelect();

private:
	void Print(WINDOW *pMenuWin, unsigned int Highlight);
} ;

extern IMenu *CreateMenu();

#endif
