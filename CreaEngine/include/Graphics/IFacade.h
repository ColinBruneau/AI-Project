/***************************************************/
/* Nom:	IFacade.h
/* Description: IFacade
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _IFacade_H
#define _IFacade_H

#include "Core\Plugin.h"
#include "Graphics\IDrawable.h"

namespace crea
{
	class IFont;
	class ITexture;
	class IntRect;
	class ILine;

	class CREAENGINE_API IFacade
	{
	public:
		~IFacade()
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
		static IFacade& get()
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

		virtual ILine* createILine(ILine* _pFrom = nullptr) = 0;

		virtual bool isKeyPressed(Key _key) = 0;

		virtual bool isMouseButtonPressed(Button _button) = 0;

		virtual Vector2f getMousePosition() = 0;

		virtual IntRect& getWindowRect() = 0;

	protected:
		IFacade()
		{
			s_Instance = NULL;
		}

	private:
		// Données membres
		static IFacade*        s_Instance; // Instance du renderer chargée
		static Plugin<IFacade> s_Library;  // Helper pour manipuler la DLL
	};

} // namespace crea

#endif // _IFacade_H