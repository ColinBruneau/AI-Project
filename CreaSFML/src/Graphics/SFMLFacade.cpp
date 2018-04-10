#include "stdafx.h"

#include "Graphics\SFMLFacade.h"
#include "Graphics\SFMLFont.h"
#include "Graphics\SFMLTexture.h"
#include "Graphics\SFMLColor.h"
#include "Graphics\SFMLText.h"
#include "Graphics\SFMLSprite.h"
#include "Graphics\SFMLLine.h"
#include "Graphics\SFMLShape.h"


namespace crea
{
	SFMLFacade::SFMLFacade() 
		: m_rWindowRect(0, 0, 1280, 800)
	{
		m_pWindow = nullptr;
	}

	SFMLFacade::~SFMLFacade()
	{
		if (m_pWindow)
		{
			delete m_pWindow;
			m_pWindow = nullptr;
		}
	}

	// Renvoie l'instance du renderer
	SFMLFacade& SFMLFacade::Instance()
	{
		static SFMLFacade s_Instance;
		return s_Instance;
	}

	void SFMLFacade::initialize()
	{
		m_pWindow = new sf::RenderWindow(sf::VideoMode((unsigned int)m_rWindowRect.getWidth(), (unsigned int)m_rWindowRect.getHeight()), "Application SFML");
	}
	
	bool SFMLFacade::update()
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

	void SFMLFacade::beginScene() const
	{
		m_pWindow->clear();
	}
	
	// Rendu d'un objet
	void SFMLFacade::draw(IDrawable& _o) const
	{
		//m_pWindow->draw(_o);
	}

	void SFMLFacade::endScene() const
	{
		m_pWindow->display();
	}

	void SFMLFacade::quit() const
	{
	}

	IFont* SFMLFacade::createIFont(IFont* _pFrom)
	{
		return (_pFrom ? new SFMLFont(*(SFMLFont*)_pFrom) : new SFMLFont);
	}

	void SFMLFacade::destroyIFont(IFont* _pFont)
	{
		delete _pFont;
	}

	ITexture* SFMLFacade::createITexture(ITexture* _pFrom)
	{
		return (_pFrom ? new SFMLTexture(*(SFMLTexture*)_pFrom) : new SFMLTexture);
	}

	void SFMLFacade::destroyITexture(ITexture* _pTexture)
	{
		delete _pTexture;
	}

	IColor* SFMLFacade::createIColor(IColor* _pFrom)
	{
		return (_pFrom ? new SFMLColor(*(SFMLColor*)_pFrom) : new SFMLColor);
	}

	void SFMLFacade::destroyIColor(IColor* _pColor)
	{
		delete _pColor;
	}

	IText* SFMLFacade::createIText(IText* _pFrom)
	{
		return (_pFrom ? new SFMLText(*(SFMLText*)_pFrom) : new SFMLText);
	}

	void SFMLFacade::destroyIText(IText* _pText)
	{
		delete _pText;
	}

	ISprite* SFMLFacade::createISprite(ISprite* _pFrom)
	{
		return (_pFrom ? new SFMLSprite(*(SFMLSprite*)_pFrom) : new SFMLSprite);
	}

	void SFMLFacade::destroyISprite(ISprite* _pSprite)
	{
		delete _pSprite;
	}

	ILine* SFMLFacade::createILine(ILine* _pFrom)
	{
		return (_pFrom ? new SFMLLine(*(SFMLLine*)_pFrom) : new SFMLLine);
	}

	void SFMLFacade::destroyILine(ILine* _pLine)
	{
		delete _pLine;
	}

	IShape* SFMLFacade::createIShape(IShape* _pFrom)
	{
		return (_pFrom ? new SFMLShape(*(SFMLShape*)_pFrom) : new SFMLShape);
	}

	void SFMLFacade::destroyIShape(IShape* _pShape)
	{
		delete _pShape;
	}

	IRectangleShape* SFMLFacade::createIRectangleShape(IRectangleShape* _pFrom)
	{
		return (_pFrom ? new SFMLRectangleShape(*(SFMLRectangleShape*)_pFrom) : new SFMLRectangleShape);
	}

	void SFMLFacade::destroyIRectangleShape(IRectangleShape* _pShape)
	{
		delete _pShape;
	}	

	bool SFMLFacade::isKeyPressed(Key _key)
	{
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)_key)) // Key mapping is the same as SFML
		{
			return true;
		}
		return false;
	}

	bool SFMLFacade::isMouseButtonPressed(Button _button)
	{
		if (sf::Mouse::isButtonPressed((sf::Mouse::Button)_button)) // Mouse mapping is the same as SFML
		{
			return true;
		}
		return false;
	}

	Vector2f SFMLFacade::getMousePosition()
	{
		sf::Vector2i vMousePosition = sf::Mouse::getPosition(*m_pWindow); // Get position relative to window
		return Vector2f((float) vMousePosition.x, (float)vMousePosition.y);
	}

	extern "C" __declspec(dllexport) SFMLFacade* StartPlugin()
	{
		return &SFMLFacade::Instance();
	}

} // namespace crea