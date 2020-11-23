/***************************************************/
/* Nom:	Sprite.h
/* Description: Sprite
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _Sprite_H
#define _Sprite_H

namespace crea
{

	class CREAENGINE_API Sprite
	{
	public:

		Sprite() {}
		
		virtual ~Sprite() {}

		virtual void draw() {}

		virtual void setTexture(Texture* _pTexture) {}

		virtual void setPosition(float _x, float _y) {}

		virtual void setTextureRect(int _x, int _y, int _w, int _h) {}

		virtual void setScale(float _x, float _y) {}

		virtual void setOrigin(float _x, float _y) {}

		virtual Sprite* clone() { return new Sprite(*this); }
	};

} // namespace crea

#endif // _Sprite_H