/***************************************************/
/* Nom:	GL3Facade.h
/* Description: GL3Facade
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _GL3Facade_H
#define _GL3Facade_H

#include "Graphics\IFacade.h"


namespace crea
{
	class GL3Facade
	{
		GLFWwindow* window;

		int m_iR, m_iG, m_iB;
		LPCTSTR m_szWindowName;

		// window
		IntRect m_rWindowRect;

		// Keyboard
		bool m_abKeys[101];

		// Mouse
		int m_iMousePosX;
		int m_iMousePosY;
		bool m_bMouseLeftButtonDown;
		bool m_bMouseRightButtonDown;

	private:
		// Données membres
		GL3Facade();

		void keyDown(WPARAM _wParam, bool _bDown);
		static LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		void setMousePosition(int _iX, int _iY) { m_iMousePosX = _iX; m_iMousePosY = _iY; }
		void setMouseButtonsDown(bool _bLeftButtonDown, bool _bRightButtonDown) { m_bMouseLeftButtonDown = _bLeftButtonDown; m_bMouseRightButtonDown = _bRightButtonDown; }
		bool setCursor(bool _bVisible);

	public:
		~GL3Facade();

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

		virtual IFont* createIFont(IFont* _pFrom = nullptr);

		virtual Texture* createTexture(Texture* _pFrom = nullptr);

		virtual Color* createColor(Color* _pFrom = nullptr);

		virtual Text* createText(Text* _pFrom = nullptr);

		virtual Sprite* createSprite(Sprite* _pFrom = nullptr);

		virtual bool isKeyPressed(Key _key);

		virtual bool isMouseButtonPressed(Button _button);

		virtual Vector2f getMousePosition();

		virtual IntRect& getWindowRect() { return m_rWindowRect; }

	};

} // namespace crea

#endif // _GL3Facade_H
