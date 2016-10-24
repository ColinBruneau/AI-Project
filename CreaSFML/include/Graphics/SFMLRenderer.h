/***************************************************/
/* Nom:	SFMLRenderer.h
/* Description: SFMLRenderer
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _SFMLRenderer_H
#define _SFMLRenderer_H

#include "Graphics\IRenderer.h"

#include <SFML/Graphics.hpp>

namespace crea
{
	class SFMLRenderer
	{

	private:
		// Données membres
		SFMLRenderer();

	public:
		~SFMLRenderer();

		// Renvoie l'instance du renderer
		static SFMLRenderer& Instance();

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

		virtual bool isKeyPressed(char _key);

		sf::RenderWindow* m_pWindow;

	};

} // namespace crea

#endif // _SFMLRenderer_H