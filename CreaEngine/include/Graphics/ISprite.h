/***************************************************/
/* Nom:	ISprite.h
/* Description: ISprite
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __ISprite_H_
#define __ISprite_H_

namespace crea
{

	class CREAENGINE_API ISprite : public IDrawable
	{
	public:
		ISprite()
		{
		}

		virtual ~ISprite()
		{
		}

		virtual void draw() {};

		virtual void setTexture(ITexture* _pTexture) {}
		virtual void setPosition(float _x, float _y) {}
		virtual void setTextureRect(int _x, int _y, int _w, int _h) {}
		virtual void setScale(float _x, float _y) {}
		virtual void setOrigin(float _x, float _y) {}

	};

} // namespace crea

#endif