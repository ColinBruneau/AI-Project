#include "stdafx.h"

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

namespace crea
{

	GL3Facade::GL3Facade()
		: m_rWindowRect(0, 0, 1280, 800),
		keysMap{
			GLFW_KEY_Q,            ///< The A key in AZERTY
			GLFW_KEY_B,            ///< The B key
			GLFW_KEY_C,            ///< The C key
			GLFW_KEY_D,            ///< The D key
			GLFW_KEY_E,            ///< The E key
			GLFW_KEY_F,            ///< The F key
			GLFW_KEY_G,            ///< The G key
			GLFW_KEY_H,            ///< The H key
			GLFW_KEY_I,            ///< The I key
			GLFW_KEY_J,            ///< The J key
			GLFW_KEY_K,            ///< The K key
			GLFW_KEY_L,            ///< The L key
			GLFW_KEY_SEMICOLON,    ///< The M key in AZERTY
			GLFW_KEY_N,            ///< The N key
			GLFW_KEY_O,            ///< The O key
			GLFW_KEY_P,            ///< The P key
			GLFW_KEY_A,            ///< The Q key in AZERTY
			GLFW_KEY_R,            ///< The R key
			GLFW_KEY_S,            ///< The S key
			GLFW_KEY_T,            ///< The T key
			GLFW_KEY_U,            ///< The U key
			GLFW_KEY_V,            ///< The V key
			GLFW_KEY_Z,            ///< The W key in AZERTY
			GLFW_KEY_X,            ///< The X key
			GLFW_KEY_Y,            ///< The Y key
			GLFW_KEY_W,            ///< The Z key in AZERTY
			GLFW_KEY_0,            ///< The 0 key
			GLFW_KEY_1,            ///< The 1 key
			GLFW_KEY_2,            ///< The 2 key
			GLFW_KEY_3,            ///< The 3 key
			GLFW_KEY_4,            ///< The 4 key
			GLFW_KEY_5,            ///< The 5 key
			GLFW_KEY_6,            ///< The 6 key
			GLFW_KEY_7,            ///< The 7 key
			GLFW_KEY_8,            ///< The 8 key
			GLFW_KEY_9,            ///< The 9 key
			GLFW_KEY_ESCAPE,       ///< The Escape key
			GLFW_KEY_LEFT_CONTROL,     ///< The left Control key
			GLFW_KEY_LEFT_SHIFT,       ///< The left Shift key
			GLFW_KEY_LEFT_ALT,         ///< The left Alt key
			GLFW_KEY_LEFT_SUPER,      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
			GLFW_KEY_RIGHT_CONTROL,     ///< The right Control key
			GLFW_KEY_RIGHT_SHIFT,       ///< The right Shift key
			GLFW_KEY_RIGHT_ALT,         ///< The right Alt key
			GLFW_KEY_RIGHT_SUPER,      ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
			GLFW_KEY_MENU,         ///< The Menu key
			GLFW_KEY_LEFT_BRACKET,     ///< The [ key
			GLFW_KEY_RIGHT_BRACKET,     ///< The ] key
			GLFW_KEY_M,			 ///< The ; key in AZERTY
			GLFW_KEY_COMMA,        ///< The , key
			GLFW_KEY_PERIOD,       ///< The . key
			GLFW_KEY_APOSTROPHE,        ///< The ' key
			GLFW_KEY_SLASH,        ///< The / key
			GLFW_KEY_BACKSLASH,    ///< The \ key
			GLFW_KEY_UNKNOWN,        ///< The ~ key
			GLFW_KEY_EQUAL,        ///< The = key
			GLFW_KEY_MINUS,         ///< The - key
			GLFW_KEY_SPACE,        ///< The Space key
			GLFW_KEY_ENTER,       ///< The Return key
			GLFW_KEY_BACKSPACE,    ///< The Backspace key
			GLFW_KEY_TAB,          ///< The Tabulation key
			GLFW_KEY_PAGE_UP,       ///< The Page up key
			GLFW_KEY_PAGE_DOWN,     ///< The Page down key
			GLFW_KEY_END,          ///< The End key
			GLFW_KEY_HOME,         ///< The Home key
			GLFW_KEY_INSERT,       ///< The Insert key
			GLFW_KEY_DELETE,       ///< The Delete key
			GLFW_KEY_KP_ADD,          ///< The + key
			GLFW_KEY_KP_SUBTRACT,     ///< The - key
			GLFW_KEY_KP_MULTIPLY,     ///< The * key
			GLFW_KEY_KP_DIVIDE,       ///< The / key
			GLFW_KEY_LEFT,         ///< Left arrow
			GLFW_KEY_RIGHT,        ///< Right arrow
			GLFW_KEY_UP,           ///< Up arrow
			GLFW_KEY_DOWN,         ///< Down arrow
			GLFW_KEY_KP_0,      ///< The numpad 0 key
			GLFW_KEY_KP_1,      ///< The numpad 1 key
			GLFW_KEY_KP_2,      ///< The numpad 2 key
			GLFW_KEY_KP_3,      ///< The numpad 3 key
			GLFW_KEY_KP_4,      ///< The numpad 4 key
			GLFW_KEY_KP_5,      ///< The numpad 5 key
			GLFW_KEY_KP_6,      ///< The numpad 6 key
			GLFW_KEY_KP_7,      ///< The numpad 7 key
			GLFW_KEY_KP_8,      ///< The numpad 8 key
			GLFW_KEY_KP_9,      ///< The numpad 9 key
			GLFW_KEY_F1,           ///< The F1 key
			GLFW_KEY_F2,           ///< The F2 key
			GLFW_KEY_F3,           ///< The F3 key
			GLFW_KEY_F4,           ///< The F4 key
			GLFW_KEY_F5,           ///< The F5 key
			GLFW_KEY_F6,           ///< The F6 key
			GLFW_KEY_F7,           ///< The F7 key
			GLFW_KEY_F8,           ///< The F8 key
			GLFW_KEY_F9,           ///< The F9 key
			GLFW_KEY_F10,          ///< The F10 key
			GLFW_KEY_F11,          ///< The F11 key
			GLFW_KEY_F12,          ///< The F12 key
			GLFW_KEY_F13,          ///< The F13 key
			GLFW_KEY_F14,          ///< The F14 key
			GLFW_KEY_F15,          ///< The F15 key
			GLFW_KEY_PAUSE,        ///< The Pause key
	}
	{
		m_ClearColor.setValues(0, 0, 0, 255);

		m_szWindowTitle = "Application OpenGL3";
		
		m_iMousePosX = -1;
		m_iMousePosY = -1;
		m_bMouseLeftButtonDown = false;
		m_bMouseRightButtonDown = false;

		m_bDepthTest = false;
	}

	GL3Facade::~GL3Facade()
	{

	}

	void GL3Facade::setWindowSize(int _width, int _height)
	{
		m_rWindowRect.m_iW = _width;
		m_rWindowRect.m_iH = _height;

		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, m_rWindowRect.m_iW, m_rWindowRect.m_iH);
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
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			return true; // prevent Windows from setting cursor to window class cursor
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		return false;
	}

	void GL3Facade::setDepthTest(bool _bDepthTest)
	{
		m_bDepthTest = _bDepthTest;
		if (m_bDepthTest)
		{
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
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
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif


		// Open a window and create its OpenGL context
		window = glfwCreateWindow(m_rWindowRect.m_iW, m_rWindowRect.m_iH, m_szWindowTitle.c_str(), NULL, NULL);
		if (window == NULL) {
			cout << "Failed to create GLFW window" << endl;
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(window); // Initialize GLEW
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);

		// tell GLFW to capture our mouse
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}

		// configure global opengl state
		// -----------------------------
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
	}
	
	bool GL3Facade::update()
	{
		// render loop
		// -----------
		while (!glfwWindowShouldClose(window))
		{
			return true;
		}

		return false;
	}

	void GL3Facade::beginScene() const
	{
		glClearColor(m_ClearColor.getR(), m_ClearColor.getG(), m_ClearColor.getB(), m_ClearColor.getA());
		if (m_bDepthTest)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
		}
		else
		{
			glClear(GL_COLOR_BUFFER_BIT);
		}
	}
	
	// Rendu d'un objet
	void GL3Facade::draw(IDrawable& _o) const
	{

	}

	void GL3Facade::endScene() const
	{
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void GL3Facade::quit()
	{
		UnregisterClass("GL3Facade", GetModuleHandle(NULL)); // CB: to do, keep the instance to unregister it

		// glfw: terminate, clearing all previously allocated GLFW resources.
		// ------------------------------------------------------------------
		glfwTerminate();
	}

	Font* GL3Facade::createFont(Font* _pFrom)
	{
		return (_pFrom ? new GL3Font(*(GL3Font*)_pFrom) : new GL3Font);
	}

	void GL3Facade::destroyFont(Font* _pFont)
	{
		delete ((GL3Font*)_pFont);
	}

	Texture* GL3Facade::createTexture(Texture* _pFrom)
	{
		return (_pFrom ? new GL3Texture(*(GL3Texture*)_pFrom) : new GL3Texture);
	}

	void GL3Facade::destroyTexture(Texture* _pTexture)
	{
		delete ((GL3Texture*)_pTexture);
	}

	Color* GL3Facade::createColor(Color* _pFrom)
	{
		return (_pFrom ? new GL3Color(*(GL3Color*)_pFrom) : new GL3Color);
	}

	void GL3Facade::destroyColor(Color* _pColor)
	{
		delete ((GL3Color*)_pColor);
	}

	Text* GL3Facade::createText(Text* _pFrom)
	{
		return (_pFrom ? new GL3Text(*(GL3Text*)_pFrom) : new GL3Text);
	}

	void GL3Facade::destroyText(Text* _pText)
	{
		delete ((GL3Text*)_pText);
	}

	Sprite* GL3Facade::createSprite(Sprite* _pFrom)
	{
		return (_pFrom ? new GL3Sprite(*(GL3Sprite*)_pFrom) : new GL3Sprite);
	}

	void GL3Facade::destroySprite(Sprite* _pSprite)
	{
		delete ((GL3Sprite*)_pSprite);
	}

	Shape* GL3Facade::createShape(string _szType, Shape* _pFrom)
	{
		if (_szType == "Default")
		{
			return (_pFrom ? new GL3Shape(*(GL3Shape*)_pFrom) : new GL3Shape);
		}
		else if (_szType == "Rectangle")
		{
			return (_pFrom ? new GL3RectangleShape(*(GL3RectangleShape*)_pFrom) : new GL3RectangleShape);
		}
		else if (_szType == "Circle")
		{
			return (_pFrom ? new GL3CircleShape(*(GL3CircleShape*)_pFrom) : new GL3CircleShape);
		}
		else if (_szType == "Arrow")
		{
			return (_pFrom ? new GL3ArrowShape(*(GL3ArrowShape*)_pFrom) : new GL3ArrowShape);
		}
		else if (_szType == "Line")
		{
			return (_pFrom ? new GL3LineShape(*(GL3LineShape*)_pFrom) : new GL3LineShape);
		}
		return nullptr;
	}

	void GL3Facade::destroyShape(Shape* _pShape)
	{
		delete _pShape;
	}

	Shader* GL3Facade::createShader(Shader* _pFrom)
	{
		return (_pFrom ? new GL3Shader(*(GL3Shader*)_pFrom) : new GL3Shader);
	}

	void GL3Facade::destroyShader(Shader* _pShader)
	{
		delete _pShader;
	}

	Material* GL3Facade::createMaterial(Material* _pFrom)
	{
		return (_pFrom ? new GL3Material(*(GL3Material*)_pFrom) : new GL3Material);
	}

	void GL3Facade::destroyMaterial(Material* _pMaterial)
	{
		delete _pMaterial;
	}

	bool GL3Facade::isKeyPressed(Key _key)
	{
		return (glfwGetKey(window, keysMap[_key]) == GLFW_PRESS);
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

	// glfw: whenever the window size changed (by OS or user resize) this callback function executes
	// ---------------------------------------------------------------------------------------------
	void framebuffer_size_callback(GLFWwindow* window, int _width, int _height)
	{
		GL3Facade* pGL3Facade = (GL3Facade*) GameManager::getSingleton()->getRenderer();
		pGL3Facade->setWindowSize(_width, _height);
	}

	// glfw: whenever the mouse moves, this callback is called
	// -------------------------------------------------------
	void mouse_callback(GLFWwindow* window, double _xPos, double _yPos)
	{
		// todo: handle mouse move
		//InputManager::getSingleton()->setMousePosition(_xPos, _yPos);
	}

	// glfw: whenever the mouse scroll wheel scrolls, this callback is called
	// ----------------------------------------------------------------------
	void scroll_callback(GLFWwindow* window, double _xOffset, double _yOffset)
	{
		// todo: handle mouse scroll
		//InputManager::getSingleton()->setMouseScroll(_xOffset, _yOffset);
	}
} // namespace crea