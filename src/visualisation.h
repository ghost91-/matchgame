#ifndef VISUALISATION_DEFINED
#define VISUALISATION_DEFINED

class CPlayfield;

class IVisualisation
{
	public:
	virtual ~IVisualisation() {}
	virtual void ShowField(CPlayfield *pField) = 0;
} ;

class CVisualisation : public IVisualisation
{
	public:
	void ShowField(CPlayfield *pField);
} ;

extern IVisualisation *CreateVisualisation();

#endif
