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

		virtual IFont* createIFont(IFont* _pFrom = nullptr);

		virtual void destroyIFont(IFont* _pFont);

		virtual ITexture* createITexture(ITexture* _pFrom = nullptr);

		virtual void destroyITexture(ITexture* _pTexture);

		virtual IColor* createIColor(IColor* _pFrom = nullptr);

		virtual void destroyIColor(IColor* _pColor);

		virtual IText* createIText(IText* _pFrom = nullptr);

		virtual void destroyIText(IText* _pText);

		virtual ISprite* createISprite(ISprite* _pFrom = nullptr);

		virtual void destroyISprite(ISprite* _pSprite);

		virtual ILine* createILine(ILine* _pFrom = nullptr);

		virtual void destroyILine(ILine* _pLine);

		virtual IShape* createIShape(IShape* _pFrom = nullptr);

		virtual void destroyIShape(IShape* _pShape);

		virtual IRectangleShape* createIRectangleShape(IRectangleShape* _pFrom = nullptr);

		virtual void destroyIRectangleShape(IRectangleShape* _pShape);

		virtual bool isKeyPressed(Key _key);

		virtual bool isMouseButtonPressed(Button _button);

		virtual Vector2f getMousePosition();

		virtual IntRect& getWindowRect() { return m_rWindowRect; }

		sf::RenderWindow* m_pWindow;

	};

} // namespace crea

#endif // _SFMLFacade_H