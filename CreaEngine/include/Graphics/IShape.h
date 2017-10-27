/***************************************************/
/* Nom:	IShape.h
/* Description: Shape
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _IShape_H
#define _IShape_H

namespace crea
{

	class CREAENGINE_API IShape : public IDrawable
	{
	public:
		IShape()
		{
		}

		virtual ~IShape()
		{
		}

		virtual void draw() {}

		virtual void setColor(IColor* _pColor) {};

		virtual void setOutlineColor(IColor* _pColor) {};

		virtual void setOutlineThickness(float _fPixels) {};

		virtual void setPosition(float _x, float _y) {};
	};

	class CREAENGINE_API IRectangleShape : public IShape
	{
	public:

		IRectangleShape()
		{
		}

		~IRectangleShape()
		{
		}

		virtual void setSize(float _x, float _y) {};
	};
} // namespace crea

#endif // _IShape_H