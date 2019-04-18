/***************************************************/
/* Nom:	Shape.h
/* Description: Shape
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _Shape_H
#define _Shape_H

namespace crea
{

	class CREAENGINE_API Shape
	{
	public:

		Shape() {}

		virtual ~Shape() {}

		virtual void draw() { assert(false); }

		virtual void setColor(Color* _pColor) { assert(false); }

		virtual void setOutlineColor(Color* _pColor) { assert(false); }

		virtual void setOutlineThickness(float _fPixels) { assert(false); }

		virtual void setPosition(float _x, float _y) { assert(false); }

		virtual void setRotation(float _angle) { assert(false); }

		virtual void setScale(float _x, float _y) { assert(false); }

		virtual void setOrigin(float _x, float _y) { assert(false); }
	};

	class CREAENGINE_API RectangleShape : public Shape
	{
	public:

		RectangleShape() {}

		// Todo: add const copie and operator= on all RectangleShape
		//RectangleShape(const RectangleShape& _other);
		//virtual RectangleShape& operator=(const RectangleShape& _other);

		~RectangleShape() {}

		virtual void setSize(float _x, float _y) { assert(false); }
	};

	class CREAENGINE_API CircleShape : public Shape
	{
	public:

		CircleShape() {}

		// Todo: add const copie and operator= on CircleShape
		//CircleShape(const CircleShape& _other);virtual CircleShape& operator=(const CircleShape& _other);
		//virtual CircleShape& operator=(const CircleShape& _other);

		~CircleShape() {}

		virtual void setRadius(float _r) { assert(false); }
	};

	class CREAENGINE_API ArrowShape : public Shape
	{
	public:

		ArrowShape() {}

		~ArrowShape() {}
		// Todo: add const copie and operator= on ArrowShape

		virtual void setSize(float _x, float _y) { assert(false); }

		virtual void setStartAndEnd(float _xStart, float _yStart, float _xEnd, float _yEnd) { assert(false); }
	};

	class CREAENGINE_API LineShape : public Shape
	{
	public:

		LineShape() {}

		~LineShape() {}

		// Todo: add const copie and operator= on LineShape

		virtual void setSize(float _x, float _y) { assert(false); }
		
		virtual void setStartAndEnd(float _xStart, float _yStart, float _xEnd, float _yEnd) { assert(false); }
	};
} // namespace crea

#endif // _Shape_H