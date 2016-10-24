#include "stdafx.h"

#include "Graphics\SFMLRenderer.h"
#include "Graphics\SFMLFont.h"
#include "Graphics\SFMLTexture.h"
#include "Graphics\SFMLColor.h"
#include "Graphics\SFMLText.h"
#include "Graphics\SFMLSprite.h"


namespace crea
{
	SFMLRenderer::SFMLRenderer()
	{
	}

	SFMLRenderer::~SFMLRenderer()
	{

	}

	// Renvoie l'instance du renderer
	SFMLRenderer& SFMLRenderer::Instance()
	{
		static SFMLRenderer s_Instance;
		return s_Instance;
	}

	void SFMLRenderer::initialize()
	{
		m_pWindow = new sf::RenderWindow(sf::VideoMode((unsigned int)(1280), (unsigned int)(640)), "SFML RENDERER");
	}
	
	bool SFMLRenderer::update()
	{
		if (m_pWindow->isOpen())
		{
			sf::Event event;
			while (m_pWindow->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					m_pWindow->close();
			}
			return true;
		}
		return false;
	}

	void SFMLRenderer::beginScene() const
	{
		m_pWindow->clear();
	}
	
	// Rendu d'un objet
	void SFMLRenderer::draw(IDrawable& _o) const
	{
		//m_pWindow->draw(_o);
	}

	void SFMLRenderer::endScene() const
	{
		m_pWindow->display();
	}

	void SFMLRenderer::quit() const
	{
	}

	IFont* SFMLRenderer::createIFont(IFont* _pFrom)
	{
		return (_pFrom ? new SFMLFont(*(SFMLFont*)_pFrom) : new SFMLFont);
	}

	ITexture* SFMLRenderer::createITexture(ITexture* _pFrom)
	{
		return (_pFrom ? new SFMLTexture(*(SFMLTexture*)_pFrom) : new SFMLTexture);
	}

	IColor* SFMLRenderer::createIColor(IColor* _pFrom)
	{
		return (_pFrom ? new SFMLColor(*(SFMLColor*)_pFrom) : new SFMLColor);
	}

	IText* SFMLRenderer::createIText(IText* _pFrom)
	{
		return (_pFrom ? new SFMLText(*(SFMLText*)_pFrom) : new SFMLText);
	}

	ISprite* SFMLRenderer::createISprite(ISprite* _pFrom)
	{
		return (_pFrom ? new SFMLSprite(*(SFMLSprite*)_pFrom) : new SFMLSprite);
	}

	bool SFMLRenderer::isKeyPressed(char _key)
	{
		bool bIsKeyValid = false;
		sf::Keyboard::Key sfKey = sf::Keyboard::Unknown;
		if (_key >= '0' && _key <= '9')
		{
			sfKey = (sf::Keyboard::Key) (sf::Keyboard::Num0 + _key - '0');
			bIsKeyValid = true;
		}
		else if (_key >= 'a' && _key <= 'z')
		{
			sfKey = (sf::Keyboard::Key) (sf::Keyboard::A + _key - 'a');
			bIsKeyValid = true;
		}
		if (bIsKeyValid && sf::Keyboard::isKeyPressed(sfKey))
		{
			return true;
		}
		return false;
	}

	extern "C" __declspec(dllexport) SFMLRenderer* StartPlugin()
	{
		return &SFMLRenderer::Instance();
	}

} // namespace crea