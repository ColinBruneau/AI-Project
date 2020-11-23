/***************************************************/
/* Nom:	GL3Facade.h
/* Description: GL3Facade
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _GL3Facade_H
#define _GL3Facade_H

#include "Graphics\IFacade.h"
#include "Graphics\GL3Color.h"

namespace crea
{
	class GL3Facade
	{
		GLFWwindow* window;

		string m_szWindowTitle;
		GL3Color m_ClearColor;
		
		// window
		IntRect m_rWindowRect;

		// Keyboard
		int keysMap[KeyCount];

		// Mouse
		int m_iMousePosX;
		int m_iMousePosY;
		bool m_bMouseLeftButtonDown;
		bool m_bMouseRightButtonDown;

		// Depth test
		bool m_bDepthTest;

	private:
		// Données membres
		GL3Facade();

		void setMousePosition(int _iX, int _iY) { m_iMousePosX = _iX; m_iMousePosY = _iY; }
		void setMouseButtonsDown(bool _bLeftButtonDown, bool _bRightButtonDown) { m_bMouseLeftButtonDown = _bLeftButtonDown; m_bMouseRightButtonDown = _bRightButtonDown; }
		bool setCursor(bool _bVisible);

	public:
		~GL3Facade();

		void setWindowSize(int _width, int _height);

		unsigned int getWindowWidth() { return m_rWindowRect.m_iW; }

		unsigned int getWindowHeight() { return m_rWindowRect.m_iH; }

		float getWindowAspect() { return m_rWindowRect.m_iW / (float)m_rWindowRect.m_iH; }

		inline void setWindowTitle(const string& _windowTitle) { m_szWindowTitle = _windowTitle; }

		// Renvoie l'instance du renderer
		static GL3Facade& Instance();

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
		virtual void quit();

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

		// Activate/deactivate Depth testing for 3D rendering
		void setDepthTest(bool _bDepthTest);
	};

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	void mouse_callback(GLFWwindow* window, double _xPos, double _yPos);

	void scroll_callback(GLFWwindow* window, double _xOffset, double _yOffset);

} // namespace crea

#endif // _GL3Facade_H
