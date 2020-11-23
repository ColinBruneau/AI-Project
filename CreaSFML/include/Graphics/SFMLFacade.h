/***************************************************/
/* Nom:	SFMLFacade.h
/* Description: SFMLFacade
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _SFMLFacade_H
#define _SFMLFacade_H

#include "Graphics\IFacade.h"

#include <SFML/Graphics.hpp>

namespace crea
{
	class SFMLFacade
	{
		// window
		IntRect m_rWindowRect;

	private:
		// Données membres
		SFMLFacade();

	public:
		~SFMLFacade();

		// Renvoie l'instance du renderer
		static SFMLFacade& Instance();

		// Initialise le renderer
		virtual void initialize();

		// Boucle de rendu
		virtual bool update();

		// Démarre le rendu de la scène
		virtual void beginScene() const;

		// Rendu d'un objet
		virtual void draw(IDrawable& _o) const;

		// Termine le rendu de la scène
		virtual void endScene() const;

		// Quitte le renderer
		virtual void quit() const;

		virtual Font* createFont(Font* _pFrom = nullptr);

		virtual void destroyFont(Font* _pFont);

		virtual Texture* createTexture(Texture* _pFrom = nullptr);

		virtual void destroyTexture(Texture* _pTexture);

		virtual Color* createColor(Color* _pFrom = nullptr);

		virtual void destroyColor(Color* _pColor);

		virtual Text* createText(Text* _pFrom = nullptr);

		virtual void destroyText(Text* _pText);

		virtual Sprite* createSprite(Sprite* _pFrom = nullptr);

		virtual void destroySprite(Sprite* _pSprite);

		virtual Shape* createShape(string _szType, Shape* _pFrom = nullptr);

		virtual void destroyShape(Shape* _pShape);

		virtual Shader* createShader(Shader* _pFrom = nullptr);

		virtual void destroyShader(Shader* _pShader);

		virtual Material* createMaterial(Material* _pFrom = nullptr);

		virtual void destroyMaterial(Material* _pMaterial);

		virtual bool isKeyPressed(Key _key);

		virtual bool isMouseButtonPressed(Button _button);

		virtual Vector2f getMousePosition();

		virtual IntRect& getWindowRect() { return m_rWindowRect; }

		virtual void setWindowRect(IntRect _rect) { m_rWindowRect = _rect; }

		sf::RenderWindow* m_pWindow;

	};

} // namespace crea

#endif // _SFMLFacade_H