#include "stdafx.h"

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

namespace crea
{
	GL3Facade::GL3Facade()
		: m_rWindowRect(0, 0, 1280, 800)
	{
		m_iR = 0;
		m_iG = 0;
		m_iB = 255;

		m_szWindowName = "Application OpenGL3";

		ZeroMemory(&m_abKeys, sizeof(m_abKeys));

		m_iMousePosX = -1;
		m_iMousePosY = -1;
		m_bMouseLeftButtonDown = false;
		m_bMouseRightButtonDown = false;
	}

	GL3Facade::~GL3Facade()
	{

	}

	// Renvoie l'instance du renderer
	GL3Facade& GL3Facade::Instance()
	{
		static GL3Facade s_Instance;
		return s_Instance;
	}

	bool GL3Facade::setCursor(bool _bVisible)
	{
		if (_bVisible)
		{
			// Turn off window cursor 
			SetCursor(NULL);
			//m_pDevice->ShowCursor(TRUE);
			return true; // prevent Windows from setting cursor to window class cursor
		}
		else
		{
			//SetCursor(LoadCursor(NULL, IDC_ARROW));
		}
		return false;
	}

	void GL3Facade::initialize()
	{
		// Initialise GLFW
		if (!glfwInit())
		{
			fprintf(stderr, "Failed to initialize GLFW\n");
			return;
		}

		glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

																	   // Open a window and create its OpenGL context
		window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
		if (window == NULL) {
			fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(window); // Initialize GLEW
		glewExperimental = true; // Needed in core profile
		if (glewInit() != GLEW_OK) {
			fprintf(stderr, "Failed to initialize GLEW\n");
			return;
		}
	}
	
	bool GL3Facade::update()
	{
		// Ensure we can capture the escape key being pressed below
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

		do {
			// Draw nothing, see you in tutorial 2 !

			// Swap buffers
			glfwSwapBuffers(window);
			glfwPollEvents();

		} // Check if the ESC key was pressed or the window was closed
		while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(window) == 0);

		return false;
	}

	void GL3Facade::beginScene() const
	{
		//m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET/*| D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL*/, D3DCOLOR_XRGB(m_iR, m_iG, m_iB), 1.0f, 0x00);
		//m_pDevice->BeginScene();
	}
	
	// Rendu d'un objet
	void GL3Facade::draw(IDrawable& _o) const
	{

	}

	void GL3Facade::endScene() const
	{
		//m_pDevice->EndScene();
		//m_pDevice->Present(NULL, NULL, NULL, NULL);
	}

	void GL3Facade::quit()
	{
		UnregisterClass("GL3Facade", GetModuleHandle(NULL)); // CB: to do, keep the instance to unregister it

		//release le device
		//SafeRelease(m_pDevice);

		//release l'interface GL3
		//SafeRelease(m_pD3D);
	}

	void GL3Facade::keyDown(WPARAM _wParam, bool _bDown)
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
		case VK_LWIN: m_abKeys[Key::LSystem] = _bDown; break; // CB: semble être la touche windows (à droite?)
		case VK_RCONTROL: m_abKeys[Key::RControl] = _bDown; break;
		case VK_RMENU: m_abKeys[Key::RAlt] = _bDown; break; // CB: ne semble pas fonctionner
		case VK_RWIN: m_abKeys[Key::RSystem] = _bDown; break; // CB: ?
		case VK_MENU: m_abKeys[Key::Menu] = _bDown; break; // Alt gr
		//case ?: m_abKeys[Key::LBracket] = _bDown; break; // CB: à vérifier...
		//case ?: m_abKeys[Key::RBracket] = _bDown; break; // CB: à vérifier...
		//case ?: m_abKeys[Key::SemiColon] = _bDown; break; // CB: à vérifier...
		//case ?: m_abKeys[Key::Comma] = _bDown; break; // CB: à vérifier...
		//case ?: m_abKeys[Key::Period] = _bDown; break; // CB: à vérifier...
		//case ?: m_abKeys[Key::Quote] = _bDown; break; // CB: à vérifier...
		//case ?: m_abKeys[Key::Slash] = _bDown; break; // CB: à vérifier...
		//case ?: m_abKeys[Key::BackSlash] = _bDown; break; // CB: à vérifier...
		//case ?: m_abKeys[Key::Tilde] = _bDown; break; // CB: à vérifier...
		//case ?: m_abKeys[Key::Equal] = _bDown; break; // CB: à vérifier...
		//case ?: m_abKeys[Key::Dash] = _bDown; break; // CB: à vérifier...
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

	LRESULT WINAPI GL3Facade::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_DESTROY:
			GL3Facade::Instance().quit();
			PostQuitMessage(0);
			return 0;

		case WM_KEYDOWN:
			GL3Facade::Instance().keyDown(wParam, true);
			return 0;

		case WM_KEYUP:
			GL3Facade::Instance().keyDown(wParam, false);
			return 0;

		case WM_MOUSEMOVE:
		{
			// Retrieve mouse screen position
			int x = (short)LOWORD(lParam);
			int y = (short)HIWORD(lParam);
			GL3Facade::Instance().setMousePosition(x, y);  //CB: Bug: returns 1263*760 on a 1280*800 window
			cout << x << " " << y << endl;

			// Check to see if the left button is held down:
			bool bLeftButtonDown = (wParam & MK_LBUTTON) ? true : false;

			// Check if right button down:
			bool bRightButtonDown = (wParam & MK_RBUTTON) ? true : false;
			
			GL3Facade::Instance().setMouseButtonsDown(bLeftButtonDown, bRightButtonDown);
			return 0;
		}

		case WM_PAINT:
			ValidateRect(hWnd, NULL);
			return 0;

		case WM_SETCURSOR:
			return GL3Facade::Instance().setCursor(false);
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	IFont* GL3Facade::createIFont(IFont* _pFrom)
	{
		return (_pFrom ? new GL3Font(*(GL3Font*)_pFrom) : new GL3Font);
	}

	ITexture* GL3Facade::createITexture(ITexture* _pFrom)
	{
		return (_pFrom ? new GL3Texture(*(GL3Texture*)_pFrom) : new GL3Texture);
	}

	IColor* GL3Facade::createIColor(IColor* _pFrom)
	{
		return (_pFrom ? new GL3Color(*(GL3Color*)_pFrom) : new GL3Color);
	}

	IText* GL3Facade::createIText(IText* _pFrom)
	{
		return (_pFrom ? new GL3Text(*(GL3Text*)_pFrom) : new GL3Text);
	}

	ISprite* GL3Facade::createISprite(ISprite* _pFrom)
	{
		return (_pFrom ? new GL3Sprite(*(GL3Sprite*)_pFrom) : new GL3Sprite);
	}

	bool GL3Facade::isKeyPressed(Key _key)
	{
		if (m_abKeys[_key])
		{
			return true;
		}
		return false;
	}

	bool GL3Facade::isMouseButtonPressed(Button _button)
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

	Vector2f GL3Facade::getMousePosition()
	{
		return Vector2f((float)m_iMousePosX, (float)m_iMousePosY); // Get position relative to window
	}

	extern "C" __declspec(dllexport) GL3Facade* StartPlugin()
	{
		return &GL3Facade::Instance();
	}

} // namespace crea