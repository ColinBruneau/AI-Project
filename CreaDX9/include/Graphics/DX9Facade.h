/***************************************************/
/* Nom:	DX9Facade.h
/* Description: DX9Facade
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _DX9Facade_H
#define _DX9Facade_H

#include "Graphics\IFacade.h"


namespace crea
{
	class DX9Facade
	{
		D3DPRESENT_PARAMETERS	   m_d3dpp;
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
		DX9Facade();

		HRESULT initD3D(HWND hWnd);
		void keyDown(WPARAM _wParam, bool _bDown);
		static LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		void setMousePosition(int _iX, int _iY) { m_iMousePosX = _iX; m_iMousePosY = _iY; }
		void setMouseButtonsDown(bool _bLeftButtonDown, bool _bRightButtonDown) { m_bMouseLeftButtonDown = _bLeftButtonDown; m_bMouseRightButtonDown = _bRightButtonDown; }
		bool setCursor(bool _bVisible);

	public:
		~DX9Facade();

		// Renvoie l'instance du renderer
		static DX9Facade& Instance();

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

		virtual ITexture* createITexture(ITexture* _pFrom = nullptr);

		virtual IColor* createIColor(IColor* _pFrom = nullptr);

		virtual IText* createIText(IText* _pFrom = nullptr);

		virtual ISprite* createISprite(ISprite* _pFrom = nullptr);

		virtual bool isKeyPressed(Key _key);

		virtual bool isMouseButtonPressed(Button _button);

		virtual Vector2f getMousePosition();

		virtual IntRect& getWindowRect() { return m_rWindowRect; }

		LPDIRECT3DDEVICE9 m_pDevice;
		LPDIRECT3D9 m_pD3D;
	};

} // namespace crea

#endif // _DX9Facade_H
