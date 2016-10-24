/***************************************************/
/* Nom:	IRenderer.h
/* Description: IRenderer
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _IRenderer_H
#define _IRenderer_H

#include "Core\Plugin.h"
#include "Graphics\IDrawable.h"

namespace crea
{
	class IFont;
	class ITexture;

	class CREAENGINE_API IRenderer
	{
	public:
		~IRenderer()
		{
			destroy();
		}

		// Charge un renderer à partir d'une DLL
		static void load(const std::string& DllName)
		{
			destroy();
			s_Instance = s_Library.Load(DllName);
			assert(s_Instance != NULL);
		}

		// Détruit le renderer
		static void destroy()
		{
			//delete s_Instance;
			s_Instance = NULL;
		}

		// Renvoie l'instance du renderer
		static IRenderer& get()
		{
			assert(s_Instance != NULL);
			return *s_Instance;
		}

		// Initialise le renderer
		virtual void initialize() = 0;

		// Boucle de rendu
		virtual bool update() = 0;

		// Démarre le rendu de la scène
		virtual void beginScene() const = 0;

		// Rendu d'un objet
		virtual void draw(IDrawable& _o) const = 0;

		// Termine le rendu de la scène
		virtual void endScene() const = 0;
		
		// Quitte le renderer
		virtual void quit() const = 0;

		virtual IFont* createIFont(IFont* _pFrom = nullptr) = 0;

		virtual ITexture* createITexture(ITexture* _pFrom = nullptr) = 0;

		virtual IColor* createIColor(IColor* _pFrom = nullptr) = 0;

		virtual IText* createIText(IText* _pFrom = nullptr) = 0;

		virtual ISprite* createISprite(ISprite* _pFrom = nullptr) = 0;

		virtual bool isKeyPressed(char _key) = 0;

	protected:
		IRenderer()
		{
			s_Instance = NULL;
		}

	private:
		// Données membres
		static IRenderer*        s_Instance; // Instance du renderer chargée
		static Plugin<IRenderer> s_Library;  // Helper pour manipuler la DLL
	};

} // namespace crea

#endif // _IRenderer_H