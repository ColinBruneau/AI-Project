/***************************************************/
/* Nom:	SFMLSprite.h
/* Description: SFMLSprite
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _SFMLSprite_H
#define _SFMLSprite_H

#include "Graphics\ISprite.h"

#include <SFML/Graphics.hpp>

namespace crea
{

	class SFMLSprite : public ISprite
	{
	public:
		sf::Sprite m_sprite;

		virtual void draw()
		{
			sf::RenderWindow* pWin = SFMLRenderer::Instance().m_pWindow;
			pWin->draw(this->m_sprite);
		}

		virtual void setTexture(ITexture* _pTexture)
		{
			SFMLTexture* pTexture = (SFMLTexture*)_pTexture;
			m_sprite.setTexture(pTexture->m_texture);
		}

		virtual void setPosition(float _x, float _y)
		{
			m_sprite.setPosition(sf::Vector2f(_x, _y));
		}

		virtual void setTextureRect(int _x, int _y, int _w, int _h)
		{
			m_sprite.setTextureRect(sf::IntRect(_x, _y, _w, _h));
		}
	};

} // namespace crea

#endif // _SFMLSprite_H