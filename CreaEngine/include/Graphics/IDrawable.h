/***************************************************/
/* Nom:	IDrawable.h
/* Description: IDrawable
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _IDrawable_H
#define _IDrawable_H

namespace crea
{
	class CREAENGINE_API IDrawable
	{
	public:

		IDrawable()
		{
		}

		~IDrawable()
		{
		}

		virtual void draw() = 0;
	};

} // namespace crea

#endif // _IDrawable_H