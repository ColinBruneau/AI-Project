/***************************************************/
/* Nom:	State.h
/* Description: State
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __State_H_
#define __State_H_

namespace crea
{

	class CREAENGINE_API State
	{

	public:
		State();
		virtual ~State();

		virtual bool onInit() = 0;
		virtual bool onUpdate() = 0;
		virtual bool onDraw() = 0;
		virtual bool onQuit() = 0;

	};

} // namespace crea

#endif
