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

		virtual ITexture* createITexture(ITexture* _pFrom = nullptr);

		virtual IColor* createIColor(IColor* _pFrom = nullptr);

		virtual IText* createIText(IText* _pFrom = nullptr);

		virtual ISprite* createISprite(ISprite* _pFrom = nullptr);

		virtual bool isKeyPressed(Key _key);

		virtual bool isMouseButtonPressed(Button _button);

		virtual Vector2f getMousePosition();

		sf::RenderWindow* m_pWindow;

	};

} // namespace crea

#endif // _SFMLFacade_H