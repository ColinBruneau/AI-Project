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

		MSG msg;

	private:
		// Donn�es membres
		DX9Facade();

		HRESULT initD3D(HWND hWnd);
		void keyDown(WPARAM _wParam, bool _bDown);
		static LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		void setMousePosition(int _iX, int _iY) { m_iMousePosX = _iX; m_iMousePosY = _iY; }
		void setMouseButtonsDown(bool _bLeftButtonDown, bool _bRightButtonDown) { m_bMouseLeftButtonDown = _bLeftButtonDown; m_bMouseRightButtonDown = _bRightButtonDown; }
		void setMouseLButtonDown(bool _bLeftButtonDown) { m_bMouseLeftButtonDown = _bLeftButtonDown; }
		void setMouseRButtonDown(bool _bRightButtonDown) { m_bMouseRightButtonDown = _bRightButtonDown; }
		bool setCursor(bool _bVisible);

	public:
		~DX9Facade();

		// Renvoie l'instance du renderer
		static DX9Facade& Instance();

		// Initialise le renderer
		virtual void initialize();

		// Boucle de rendu
		virtual bool update();

		// D�marre le rendu de la sc�ne
		virtual void beginScene() const;

		// Rendu d'un objet
		virtual void draw(IDrawable& _o) const;

		// Termine le rendu de la sc�ne
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

		LPDIRECT3DDEVICE9 m_pDevice;
		LPDIRECT3D9 m_pD3D;
	};

} // namespace crea

#endif // _DX9Facade_H
