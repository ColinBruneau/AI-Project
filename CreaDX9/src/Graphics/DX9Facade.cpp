#include "stdafx.h"

namespace crea
{
	DX9Facade::DX9Facade()
		: m_rWindowRect(0, 0, 1280, 800)
	{
		m_iR = 0;
		m_iG = 0;
		m_iB = 255;

		m_szWindowName = "Application DirectX9";

		ZeroMemory(&m_abKeys, sizeof(m_abKeys));

		m_iMousePosX = -1;
		m_iMousePosY = -1;
		m_bMouseLeftButtonDown = false;
		m_bMouseRightButtonDown = false;
	}

	DX9Facade::~DX9Facade()
	{

	}

	// Renvoie l'instance du renderer
	DX9Facade& DX9Facade::Instance()
	{
		static DX9Facade s_Instance;
		return s_Instance;
	}

	//-----------------------------------------------------------------------------
	// Name: initD3D()
	// Desc: Initializes Direct3D
	//-----------------------------------------------------------------------------
	HRESULT DX9Facade::initD3D(HWND hWnd)
	{
		// Create the D3D object, which is needed to create the D3DDevice
		if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
			return E_FAIL;

		// Set up the structure used to create the D3DDevice
		ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));
		m_d3dpp.Windowed = TRUE;
		m_d3dpp.BackBufferHeight = m_rWindowRect.getHeight();
		m_d3dpp.BackBufferWidth = m_rWindowRect.getWidth();
		m_d3dpp.hDeviceWindow = hWnd;
		m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		m_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		m_d3dpp.EnableAutoDepthStencil = true;
		m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

		// Create the Direct3D device
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&m_d3dpp, &m_pDevice)))
		{
			return E_FAIL;
		}

		// Device state would normally be set here

		return S_OK;
	}

	bool DX9Facade::setCursor(bool _bVisible)
	{
		if (_bVisible)
		{
			// Turn off window cursor 
			SetCursor(NULL);
			m_pDevice->ShowCursor(TRUE);
			return true; // prevent Windows from setting cursor to window class cursor
		}
		else
		{
			//SetCursor(LoadCursor(NULL, IDC_ARROW));
		}
		return false;
	}

	void DX9Facade::initialize()
	{
		// Register the window class
		WNDCLASSEX wc =
		{
			sizeof(WNDCLASSEX),
			CS_CLASSDC,
			MsgProc,
			0L,
			0L,
			GetModuleHandle(NULL),
			LoadIcon(NULL, IDI_INFORMATION), 
			LoadCursor(NULL, IDC_ARROW),
			(HBRUSH) GetStockObject(WHITE_BRUSH), 
			NULL,
			"DX9Facade", 
			LoadIcon(NULL, IDI_INFORMATION)
		};

		RegisterClassEx(&wc);

		// Create the application's window
		HWND hWnd = CreateWindow("DX9Facade", m_szWindowName,
			WS_OVERLAPPEDWINDOW, 
			m_rWindowRect.getLeft(), m_rWindowRect.getTop(), 
			m_rWindowRect.getWidth(), m_rWindowRect.getHeight(),
			NULL, NULL, wc.hInstance, NULL);

		// Initialize Direct3D
		if (SUCCEEDED(initD3D(hWnd)))
		{
			// Show the window
			ShowWindow(hWnd, SW_SHOWDEFAULT);
			UpdateWindow(hWnd);

			// Cursor
			SetCursor(LoadCursor(NULL, IDC_ARROW)); // CB: Have to force it...
		}
		else
		{
			cerr << "initD3D failed..." << endl;
		}
	}
	
	bool DX9Facade::update()
	{
		// Enter the message loop
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else return true;
		}

		return false;
	}

	void DX9Facade::beginScene() const
	{
		m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER/*| D3DCLEAR_STENCIL*/, D3DCOLOR_XRGB(m_iR, m_iG, m_iB), 1.0f, 0x00);
		m_pDevice->BeginScene();
	}
	
	// Rendu d'un objet
	void DX9Facade::draw(IDrawable& _o) const
	{

	}

	void DX9Facade::endScene() const
	{
		m_pDevice->EndScene();
		m_pDevice->Present(NULL, NULL, NULL, NULL);
	}

	void DX9Facade::quit()
	{
		UnregisterClass("DX9Facade", GetModuleHandle(NULL)); // CB: to do, keep the instance to unregister it

		//release le device
		SafeRelease(m_pDevice);

		//release l'interface DX9
		SafeRelease(m_pD3D);
	}

	void DX9Facade::keyDown(WPARAM _wParam, bool _bDown)
	{
		short nVirtKey = 0;
		switch (_wParam)
		{
		case 'A': m_abKeys[Key::A] = _bDown; break;
		case 'B': m_abKeys[Key::B] = _bDown; break;
		case 'C': m_abKeys[Key::C] = _bDown; break;
		case 'D': m_abKeys[Key::D] = _bDown; break;
		case 'E': m_abKeys[Key::E] = _bDown; break;
		case 'F': m_abKeys[Key::F] = _bDown; break;
		case 'G': m_abKeys[Key::G] = _bDown; break;
		case 'H': m_abKeys[Key::H] = _bDown; break;
		case 'I': m_abKeys[Key::I] = _bDown; break;
		case 'J': m_abKeys[Key::J] = _bDown; break;
		case 'K': m_abKeys[Key::K] = _bDown; break;
		case 'L': m_abKeys[Key::L] = _bDown; break;
		case 'M': m_abKeys[Key::M] = _bDown; break;
		case 'N': m_abKeys[Key::N] = _bDown; break;
		case 'O': m_abKeys[Key::O] = _bDown; break;
		case 'P': m_abKeys[Key::P] = _bDown; break;
		case 'Q': m_abKeys[Key::Q] = _bDown; break;
		case 'R': m_abKeys[Key::R] = _bDown; break;
		case 'S': m_abKeys[Key::S] = _bDown; break;
		case 'T': m_abKeys[Key::T] = _bDown; break;
		case 'U': m_abKeys[Key::U] = _bDown; break;
		case 'V': m_abKeys[Key::V] = _bDown; break;
		case 'W': m_abKeys[Key::W] = _bDown; break;
		case 'X': m_abKeys[Key::X] = _bDown; break;
		case 'Y': m_abKeys[Key::Y] = _bDown; break;
		case 'Z': m_abKeys[Key::Z] = _bDown; break;
		case '0': m_abKeys[Key::Num0] = _bDown; break;
		case '1': m_abKeys[Key::Num1] = _bDown; break;
		case '2': m_abKeys[Key::Num2] = _bDown; break;
		case '3': m_abKeys[Key::Num3] = _bDown; break;
		case '4': m_abKeys[Key::Num4] = _bDown; break;
		case '5': m_abKeys[Key::Num5] = _bDown; break;
		case '6': m_abKeys[Key::Num6] = _bDown; break;
		case '7': m_abKeys[Key::Num7] = _bDown; break;
		case '8': m_abKeys[Key::Num8] = _bDown; break;
		case '9': m_abKeys[Key::Num9] = _bDown; break;
		case VK_ESCAPE: m_abKeys[Key::Escape] = _bDown; break;
		case VK_CONTROL: 
			nVirtKey = GetKeyState(VK_LCONTROL);
			if ((nVirtKey & 0xff00)) m_abKeys[Key::LControl] = _bDown; 
			nVirtKey = GetKeyState(VK_RCONTROL);
			if ((nVirtKey & 0xff00)) m_abKeys[Key::RControl] = _bDown;
			break;
		case VK_SHIFT:
			nVirtKey = GetKeyState(VK_LSHIFT);
			if ((nVirtKey & 0xff00)) 
				m_abKeys[Key::LShift] = _bDown;
			nVirtKey = GetKeyState(VK_RSHIFT);
			if ((nVirtKey & 0xff00)) 
				m_abKeys[Key::RShift] = _bDown;
			break; 
		case VK_LMENU: m_abKeys[Key::LAlt] = _bDown; break; // CB: ne semble pas fonctionner
		case VK_LWIN: m_abKeys[Key::LSystem] = _bDown; break; // CB: semble �tre la touche windows (� droite?)
		case VK_RCONTROL: m_abKeys[Key::RControl] = _bDown; break;
		case VK_RMENU: m_abKeys[Key::RAlt] = _bDown; break; // CB: ne semble pas fonctionner
		case VK_RWIN: m_abKeys[Key::RSystem] = _bDown; break; // CB: ?
		case VK_MENU: m_abKeys[Key::Menu] = _bDown; break; // Alt gr
		//case ?: m_abKeys[Key::LBracket] = _bDown; break; // CB: � v�rifier...
		//case ?: m_abKeys[Key::RBracket] = _bDown; break; // CB: � v�rifier...
		//case ?: m_abKeys[Key::SemiColon] = _bDown; break; // CB: � v�rifier...
		//case ?: m_abKeys[Key::Comma] = _bDown; break; // CB: � v�rifier...
		//case ?: m_abKeys[Key::Period] = _bDown; break; // CB: � v�rifier...
		//case ?: m_abKeys[Key::Quote] = _bDown; break; // CB: � v�rifier...
		//case ?: m_abKeys[Key::Slash] = _bDown; break; // CB: � v�rifier...
		//case ?: m_abKeys[Key::BackSlash] = _bDown; break; // CB: � v�rifier...
		//case ?: m_abKeys[Key::Tilde] = _bDown; break; // CB: � v�rifier...
		//case ?: m_abKeys[Key::Equal] = _bDown; break; // CB: � v�rifier...
		//case ?: m_abKeys[Key::Dash] = _bDown; break; // CB: � v�rifier...
		case VK_SPACE: m_abKeys[Key::Space] = _bDown; break;
		case VK_RETURN: m_abKeys[Key::Return] = _bDown; break; 
		case VK_BACK: m_abKeys[Key::BackSpace] = _bDown; break; 
		case VK_TAB: m_abKeys[Key::Tab] = _bDown; break; 
		case VK_PRIOR: m_abKeys[Key::PageUp] = _bDown; break; 
		case VK_NEXT: m_abKeys[Key::PageDown] = _bDown; break; 
		case VK_END: m_abKeys[Key::End] = _bDown; break; 
		case VK_HOME: m_abKeys[Key::Home] = _bDown; break; 
		case VK_INSERT: m_abKeys[Key::Insert] = _bDown; break; 
		case VK_DELETE: m_abKeys[Key::Delete] = _bDown; break; 
		case VK_ADD: m_abKeys[Key::Add] = _bDown; break;
		case VK_SUBTRACT: m_abKeys[Key::Subtract] = _bDown; break; 
		case VK_MULTIPLY: m_abKeys[Key::Multiply] = _bDown; break; 
		case VK_DIVIDE: m_abKeys[Key::Divide] = _bDown; break; 
		case VK_LEFT: m_abKeys[Key::Left] = _bDown; break;
		case VK_RIGHT: m_abKeys[Key::Right] = _bDown; break;
		case VK_UP: m_abKeys[Key::Up] = _bDown; break;
		case VK_DOWN: m_abKeys[Key::Down] = _bDown; break;
		case VK_NUMPAD0: m_abKeys[Key::Numpad0] = _bDown; break;
		case VK_NUMPAD1: m_abKeys[Key::Numpad1] = _bDown; break;
		case VK_NUMPAD2: m_abKeys[Key::Numpad2] = _bDown; break;
		case VK_NUMPAD3: m_abKeys[Key::Numpad3] = _bDown; break;
		case VK_NUMPAD4: m_abKeys[Key::Numpad4] = _bDown; break;
		case VK_NUMPAD5: m_abKeys[Key::Numpad5] = _bDown; break;
		case VK_NUMPAD6: m_abKeys[Key::Numpad6] = _bDown; break;
		case VK_NUMPAD7: m_abKeys[Key::Numpad7] = _bDown; break;
		case VK_NUMPAD8: m_abKeys[Key::Numpad8] = _bDown; break;
		case VK_NUMPAD9: m_abKeys[Key::Numpad9] = _bDown; break;
		case VK_F1: m_abKeys[Key::F1] = _bDown; break;
		case VK_F2: m_abKeys[Key::F2] = _bDown; break;
		case VK_F3: m_abKeys[Key::F3] = _bDown; break;
		case VK_F4: m_abKeys[Key::F4] = _bDown; break;
		case VK_F5: m_abKeys[Key::F5] = _bDown; break;
		case VK_F6: m_abKeys[Key::F6] = _bDown; break;
		case VK_F7: m_abKeys[Key::F7] = _bDown; break;
		case VK_F8: m_abKeys[Key::F8] = _bDown; break;
		case VK_F9: m_abKeys[Key::F9] = _bDown; break;
		case VK_F10: m_abKeys[Key::F10] = _bDown; break;
		case VK_F11: m_abKeys[Key::F11] = _bDown; break;
		case VK_F12: m_abKeys[Key::F12] = _bDown; break;
		case VK_F13: m_abKeys[Key::F13] = _bDown; break;
		case VK_F14: m_abKeys[Key::F14] = _bDown; break;
		case VK_F15: m_abKeys[Key::F15] = _bDown; break;
		case VK_PAUSE: m_abKeys[Key::Pause] = _bDown; break;
		default:
			cerr << "Key not recognized: " << _wParam << endl;
			break;
		}
		
	}

	LRESULT WINAPI DX9Facade::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_DESTROY:
			DX9Facade::Instance().quit();
			PostQuitMessage(0);
			return 0;

		case WM_KEYDOWN:
			DX9Facade::Instance().keyDown(wParam, true);
			return 0;

		case WM_KEYUP:
			DX9Facade::Instance().keyDown(wParam, false);
			return 0;

		case WM_MOUSEMOVE:
		{
			// Retrieve mouse screen position
			int x = (short)LOWORD(lParam);
			int y = (short)HIWORD(lParam);
			DX9Facade::Instance().setMousePosition(x, y);  //CB: Bug: returns 1263*760 on a 1280*800 window
			cout << x << " " << y << endl;

			// Check to see if the left button is held down:
			bool bLeftButtonDown = (wParam & MK_LBUTTON) ? true : false;

			// Check if right button down:
			bool bRightButtonDown = (wParam & MK_RBUTTON) ? true : false;
			
			DX9Facade::Instance().setMouseButtonsDown(bLeftButtonDown, bRightButtonDown);
			return 0;
		}

		case WM_PAINT:
			ValidateRect(hWnd, NULL);
			return 0;

		case WM_SETCURSOR:
			return DX9Facade::Instance().setCursor(false);
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	Font* DX9Facade::createFont(Font* _pFrom)
	{
		return (_pFrom ? new DX9Font(*(DX9Font*)_pFrom) : new DX9Font);
	}

	void DX9Facade::destroyIFont(IFont* _pFont)
	{
		delete ((DX9Font*)_pFont);
	}

	ITexture* DX9Facade::createITexture(ITexture* _pFrom)
	{
		return (_pFrom ? new DX9Texture(*(DX9Texture*)_pFrom) : new DX9Texture);
	}

	void DX9Facade::destroyITexture(ITexture* _pTexture)
	{
		delete ((DX9Texture*)_pTexture);
	}

	IColor* DX9Facade::createIColor(IColor* _pFrom)
	{
		return (_pFrom ? new DX9Color(*(DX9Color*)_pFrom) : new DX9Color);
	}

	void DX9Facade::destroyIColor(IColor* _pColor)
	{
		delete ((DX9Color*)_pColor);
	}

	IText* DX9Facade::createIText(IText* _pFrom)
	{
		return (_pFrom ? new DX9Text(*(DX9Text*)_pFrom) : new DX9Text);
	}

	void DX9Facade::destroyIText(IText* _pText)
	{
		delete ((DX9Text*)_pText);
	}

	ISprite* DX9Facade::createISprite(ISprite* _pFrom)
	{
		return (_pFrom ? new DX9Sprite(*(DX9Sprite*)_pFrom) : new DX9Sprite);
	}

	void DX9Facade::destroyISprite(ISprite* _pSprite)
	{
		delete ((DX9Sprite*)_pSprite);
	}

	ILine* DX9Facade::createILine(ILine* _pFrom)
	{
		return (_pFrom ? new DX9Line(*(DX9Line*)_pFrom) : new DX9Line);
	}

	void DX9Facade::destroyILine(ILine* _pLine)
	{
		delete ((DX9Line*)_pLine);
	}

	IShape* DX9Facade::createIShape(IShape* _pFrom)
	{
		return (_pFrom ? new DX9Shape(*(DX9Shape*)_pFrom) : new DX9Shape);
	}

	void DX9Facade::destroyIShape(IShape* _pShape)
	{
		delete ((DX9Shape*)_pShape);
	}

	IRectangleShape* DX9Facade::createIRectangleShape(IRectangleShape* _pFrom)
	{
		return (_pFrom ? new DX9RectangleShape(*(DX9RectangleShape*)_pFrom) : new DX9RectangleShape);
	}

	void DX9Facade::destroyIRectangleShape(IRectangleShape* _pRectangleShape)
	{
		delete ((DX9RectangleShape*)_pRectangleShape);
	}

	bool DX9Facade::isKeyPressed(Key _key)
	{
		if (m_abKeys[_key])
		{
			return true;
		}
		return false;
	}

	bool DX9Facade::isMouseButtonPressed(Button _button)
	{
		if (_button == MouseLeft)
		{
			return m_bMouseLeftButtonDown;
		}
		else if (_button == MouseRight)
		{
			return m_bMouseRightButtonDown;
		}
		else
		{
			cerr << "Mouse button not recognized: " << _button << endl;
		}
		return false;
	}

	Vector2f DX9Facade::getMousePosition()
	{
		return Vector2f((float)m_iMousePosX, (float)m_iMousePosY); // Get position relative to window
	}

	extern "C" __declspec(dllexport) DX9Facade* StartPlugin()
	{
		return &DX9Facade::Instance();
	}

} // namespace crea