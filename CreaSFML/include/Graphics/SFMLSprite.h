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
		sf::Sprite* m_pSprite;

		SFMLSprite()
		{
			m_pSprite = new sf::Sprite;
		}

		~SFMLSprite()
		{
			delete m_pSprite;
		}

		virtual void draw()
		{
			sf::RenderWindow* pWin = SFMLFacade::Instance().m_pWindow;
			pWin->draw(*m_pSprite);
		}

		virtual void setTexture(Texture* _pTexture)
		{
			m_pSprite->setTexture(*((SFMLTexture*)_pTexture)->m_pTexture);
		}

		virtual void setPosition(float _x, float _y)
		{
			m_pSprite->setPosition(_x, _y);
		}

		virtual void setTextureRect(int _x, int _y, int _w, int _h)
		{
			m_pSprite->setTextureRect(sf::IntRect(_x, _y, _w, _h));
		}

		virtual void setScale(float _x, float _y)
		{
			m_pSprite->setScale(_x, _y);
		}

		virtual void setOrigin(float _x, float _y)
		{
			m_pSprite->setOrigin(_x, _y);
		}
	};

} // namespace crea

#endif // _SFMLSprite_H