/***************************************************/
/* Nom:	SFMLSprite.h
/* Description: SFMLSprite
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _SFMLSprite_H
#define _SFMLSprite_H

#include "Graphics\Sprite.h"

#include <SFML/Graphics.hpp>

namespace crea
{

	class SFMLSprite : public Sprite
	{
	public:
		sf::Sprite m_sprite;

		SFMLSprite()
		{
		}

		virtual ~SFMLSprite()
		{
		}

		virtual void draw()
		{
			sf::RenderWindow* pWin = SFMLFacade::Instance().m_pWindow;
			pWin->draw(m_sprite);
		}

		virtual void setTexture(Texture* _pTexture)
		{
			m_sprite.setTexture(*((SFMLTexture*)_pTexture)->m_pTexture);
		}

		virtual void setPosition(float _x, float _y)
		{
			m_sprite.setPosition(_x, _y);
		}

		virtual void setTextureRect(int _x, int _y, int _w, int _h)
		{
			m_sprite.setTextureRect(sf::IntRect(_x, _y, _w, _h));
		}

		virtual void setScale(float _x, float _y)
		{
			m_sprite.setScale(_x, _y);
		}

		virtual void setOrigin(float _x, float _y)
		{
			m_sprite.setOrigin(_x, _y);
		}

		virtual Sprite* clone()
		{
			return new SFMLSprite(*this);
		}
	};

} // namespace crea

#endif // _SFMLSprite_H