#ifndef VISUALISATION_DEFINED
#define VISUALISATION_DEFINED

class CPlayfield;

class IVisualisation
{
	protected:
	virtual void DoShowField(CPlayfield *pField) = 0;

	public:
	virtual ~IVisualisation() {}
	void ShowField(CPlayfield *pField) { return DoShowField(pField); }
} ;

extern IVisualisation *CreateVisualisation();

#endif
