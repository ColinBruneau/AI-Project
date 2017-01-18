/***************************************************/
/* Nom:	IGraphics.h
/* Description: IGraphics
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _IGraphics_H
#define _IGraphics_H

namespace crea
{
	class CREAENGINE_API IFont
	{
	public:

		IFont()
		{
		}

		~IFont()
		{
		}

		// Initialise le Font
		virtual bool loadFromFile(string _file) { return false; }

	};

	class CREAENGINE_API ITexture
	{
	public:

		ITexture()
		{
		}

		~ITexture()
		{
		}

		// Initialise le Texture
		virtual bool loadFromFile(string _file) { return false; }
	};

	class CREAENGINE_API IText : public IDrawable
	{
	public:
		IText()
		{
		}

		virtual ~IText()
		{
		}

		virtual void draw() {};

		virtual void setFont(IFont* _pFont) {}

		virtual void setColor(IColor* _pColor) {}

		virtual void setCharacterSize(int _iSize) {}

		virtual void setString(string _szString) {}

		virtual void setPosition(float _x, float _y) {}

		virtual void setTextureRect(int _x, int _y, int _w, int _h) {}
	};

	class CREAENGINE_API IColor
	{
	public:

		IColor()
		{
		}

		~IColor()
		{
		}

		virtual void setValues(int _r, int _g, int _b, int _a) {}

	};

	class CREAENGINE_API ILine : public IDrawable
	{
	public:

		ILine()
		{
		}

		~ILine()
		{
		}

		virtual void draw() {};

		virtual void setLine(float _x1, float _y1, float _x2, float _y2) {}

		virtual void setColor(int _r, int _g, int _b, int _a) {}

	};
} // namespace crea

#endif // _IGraphics_H