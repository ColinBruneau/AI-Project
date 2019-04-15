/***************************************************/
/* Nom:	Text.h
/* Description: Text
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __Text_H_
#define __Text_H_

namespace crea
{
	class CREAENGINE_API Text
	{
	public:

		Text() {}

		virtual ~Text() {}

		virtual void draw() {}

		virtual void setFont(Font* _pFont) {}

		virtual void setColor(Color* _pColor) {}

		virtual void setCharacterSize(int _iSize) {}

		virtual void setString(string _szString) {}

		virtual void setPosition(float _x, float _y) {}

		virtual void setTextureRect(int _x, int _y, int _w, int _h) {}
	};

} // namespace crea

#endif
