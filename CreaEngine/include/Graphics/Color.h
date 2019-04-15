/***************************************************/
/* Nom:	Color.h
/* Description: Color
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _Color_H
#define _Color_H

namespace crea
{

	class CREAENGINE_API Color
	{
	public:

		Color() {}

		virtual ~Color() {}

		virtual void setValues(int _r, int _g, int _b, int _a) {}
	};

} // namespace crea

#endif // _Color_H