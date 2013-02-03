#ifndef VISUALISATION_DEFINED
#define VISUALISATION_DEFINED

class CPlayfield;
class CWindow;

class IVisualisation
{
public:
	virtual ~IVisualisation() {}
	virtual void ShowField(CPlayfield *pField) = 0;
} ;

class CVisualisation : public IVisualisation
{
private:
	CWindow *m_pWindow;
public:
	void ShowField(CPlayfield *pField);
	CVisualisation(CWindow *pWindow);
} ;

extern IVisualisation *CreateVisualisation(CWindow *pWindow);

#endif
