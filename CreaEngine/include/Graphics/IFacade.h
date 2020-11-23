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
	class Font;
	class Texture;
	class IntRect;
	class LineShape;
	class Shape;
	class RectangleShape;

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

		virtual Font* createFont(Font* _pFrom = nullptr) = 0;

		virtual void destroyFont(Font* _pFont) = 0;

		virtual Texture* createTexture(Texture* _pFrom = nullptr) = 0;

		virtual void destroyTexture(Texture* _pTexture) = 0;

		virtual Color* createColor(Color* _pFrom = nullptr) = 0;

		virtual void destroyColor(Color* _pColor) = 0;

		virtual Text* createText(Text* _pFrom = nullptr) = 0;

		virtual void destroyText(Text* _pText) = 0;

		virtual Sprite* createSprite(Sprite* _pFrom = nullptr) = 0;

		virtual void destroySprite(Sprite* _pSprite) = 0;

		virtual Shape* createShape(string _szType, Shape* _pFrom = nullptr) = 0;

		virtual void destroyShape(Shape* _pShape) = 0;

		virtual Shader* createShader(Shader* _pFrom = nullptr) = 0;

		virtual void destroyShader(Shader* _pShader) = 0;

		virtual Material* createMaterial(Material* _pFrom = nullptr) = 0;

		virtual void destroyMaterial(Material* _pMaterial) = 0;

		virtual bool isKeyPressed(Key _key) = 0;

		virtual bool isMouseButtonPressed(Button _button) = 0;

		virtual Vector2f getMousePosition() = 0;

		virtual IntRect& getWindowRect() = 0;

		virtual void setWindowRect(IntRect _rect) = 0;

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