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

	Font* SFMLFacade::createFont(Font* _pFrom)
	{
		return (_pFrom ? new SFMLFont(*(SFMLFont*)_pFrom) : new SFMLFont);
	}

	void SFMLFacade::destroyFont(Font* _pFont)
	{
		delete _pFont;
	}

	Texture* SFMLFacade::createTexture(Texture* _pFrom)
	{
		return (_pFrom ? new SFMLTexture(*(SFMLTexture*)_pFrom) : new SFMLTexture);
	}

	void SFMLFacade::destroyTexture(Texture* _pTexture)
	{
		delete _pTexture;
	}

	Color* SFMLFacade::createColor(Color* _pFrom)
	{
		return (_pFrom ? new SFMLColor(*(SFMLColor*)_pFrom) : new SFMLColor);
	}

	void SFMLFacade::destroyColor(Color* _pColor)
	{
		delete _pColor;
	}

	Text* SFMLFacade::createText(Text* _pFrom)
	{
		return (_pFrom ? new SFMLText(*(SFMLText*)_pFrom) : new SFMLText);
	}

	void SFMLFacade::destroyText(Text* _pText)
	{
		delete _pText;
	}

	Sprite* SFMLFacade::createSprite(Sprite* _pFrom)
	{
		return (_pFrom ? new SFMLSprite(*(SFMLSprite*)_pFrom) : new SFMLSprite);
	}

	void SFMLFacade::destroySprite(Sprite* _pSprite)
	{
		delete _pSprite;
	}

	Shape* SFMLFacade::createShape(string _szType, Shape* _pFrom)
	{
		if(_szType == "Default")
		{
			return (_pFrom ? new SFMLShape(*(SFMLShape*)_pFrom) : new SFMLShape);
		}		
		else if (_szType == "Rectangle")
		{
			return (_pFrom ? new SFMLRectangleShape(*(SFMLRectangleShape*)_pFrom) : new SFMLRectangleShape);
		}
		else if (_szType == "Circle")
		{
			return (_pFrom ? new SFMLCircleShape(*(SFMLCircleShape*)_pFrom) : new SFMLCircleShape);
		}
		else if (_szType == "Arrow")
		{
			return (_pFrom ? new SFMLArrowShape(*(SFMLArrowShape*)_pFrom) : new SFMLArrowShape);
		}
		else if (_szType == "Line")
		{
			return (_pFrom ? new SFMLLineShape(*(SFMLLineShape*)_pFrom) : new SFMLLineShape);
		}
		return nullptr;
	}

	void SFMLFacade::destroyShape(Shape* _pShape)
	{
		delete _pShape;
	}

	Shader* SFMLFacade::createShader(Shader* _pFrom)
	{
		// todo: implement SFML shaders
		return nullptr;
	}

	void SFMLFacade::destroyShader(Shader* _pShader)
	{
		// todo: implement SFML shaders
	}

	Material* SFMLFacade::createMaterial(Material* _pFrom)
	{
		// todo: implement SFML materials
		return nullptr;
	}

	void SFMLFacade::destroyMaterial(Material* _pMaterial)
	{
		// todo: implement SFML materials
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