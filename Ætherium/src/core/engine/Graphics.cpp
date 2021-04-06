#include "Graphics.h"
#include <core/events/WindowEvents.h>

namespace Ætherium {


	Graphics::Graphics(std::queue<Event*>* events)
	{
		hDeviceContext = NULL;
		hRenderContext = NULL;
		proxyHDC = NULL;
		proxyHWND = NULL;
		proxyRC = NULL;
		cfg = {};
		pEvents = events;
	}

	Graphics::~Graphics()
	{
		wglMakeCurrent(NULL, NULL);
		hRenderContext = NULL;
		wglDeleteContext(hRenderContext);
	}

	bool Graphics::CreateDevice(Config* cfg)
	{
		this->cfg = cfg;

		////////********* OPENGL *************///////////////


		proxyHWND = CreateWindowExW(
			0,
			cfg->GetWindowSettings().WCLASS_NAME,
			L"*******PROXY***** Ætherium Engine *****PROXY*******",
			0,
			0,
			0,
			1,
			1,
			NULL,
			NULL,
			GetModuleHandle(NULL),
			NULL
		);

		if (proxyHWND == NULL) {
			_com_error err(GetLastError());
			LOG_ERROR(L"FAILED TO CREATE PROXY WINDOW.");
			return false;
		}

		proxyHDC = GetDC(proxyHWND);


		PIXELFORMATDESCRIPTOR proxyPFD = { 0 };
		proxyPFD.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		proxyPFD.nVersion = 1;
		proxyPFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		proxyPFD.iPixelType = PFD_TYPE_RGBA;
		proxyPFD.cColorBits = cfg->GetGLSettings().colorBits;
		proxyPFD.cDepthBits = cfg->GetGLSettings().depthBits;
		proxyPFD.cStencilBits = cfg->GetGLSettings().stencilBits;
		proxyPFD.iLayerType = PFD_MAIN_PLANE;


		//  Check to see if Pixel format works
		int proxy_pixelFormatID = ChoosePixelFormat(proxyHDC, &proxyPFD);
		if (proxy_pixelFormatID == 0) {
			LOG_ERROR(L"ppfid should not be zero");
			return false;
		}
		//  IF PixelFormat is GOOD then Set the PixelFormat
		if (!SetPixelFormat(proxyHDC, proxy_pixelFormatID, &proxyPFD)) {
			LOG_ERROR(L"could not set proxy pixel format");
			return false;
		}

		//  Create RenderingContext with hDC && wglCreateContext windows GL Create Context
		proxyRC = wglCreateContext(proxyHDC);

		if (proxyRC == 0) {
			LOG_ERROR(L"proxy RenderContext should not be zero");
			return false;
		}

		// Make context current
		if (!wglMakeCurrent(proxyHDC, proxyRC)) {
			LOG_ERROR(L"Could Not Set Proxy Render Context");;
			return false;
		}

		wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(wglGetProcAddress("wglChoosePixelFormatARB"));
		if (wglChoosePixelFormatARB == nullptr) {
			LOG_ERROR(L"failed to find function definition: wglChoosePixelFormatARB");
			return false;
		}

		wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
		if (wglCreateContextAttribsARB == nullptr) {
			LOG_ERROR(L"failed to find function definition: wglCreateContextAttribsARB");
			return false;
		}

		return true;
	}

	bool Graphics::InitLoaders() {

		if (!gladLoadGL()) {

			std::cout << "could not initilize glad" << std::endl;
			return false;
		}

		return true;
	}

	bool Graphics::InitilizeScene()
	{
		// NEEDS A HOME vvvvv
		if (!InitLoaders()) {
			return false;
		}

		// Load some shaders...
		const char* vertexShaderSource =
			"#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"layout (location = 1) in vec4 aColor;\n"
			"out vec4 COLOR;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos, 1.0);\n"
			"   COLOR = aColor;\n"
			"}\0";
		const char* fragmentShaderSource =
			"#version 330 core\n"
			"out vec4 FragColor;\n"
			"in vec4 COLOR;\n"
			"void main()\n"
			"{\n"
			"  FragColor = COLOR;\n"
			"}";


		// LOAD SOME STUFF!!!


		float vertices[] = {
			 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		};
		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		unsigned int vbo;
		glGenBuffers(1, &vbo);
		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		unsigned int EBO;
		glGenBuffers(1, &EBO);


		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color                                        
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

		glCompileShader(vertexShader);
		int  success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}


		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);


		unsigned int shaderProgram;
		shaderProgram = glCreateProgram();

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);




		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);


		// for now
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		return true;

	}

	// CREATE CONTEXT 
	// [ ]  SET HDC to the deviceContext found in the created handetoWindow
	// [ ]  SET PIXEL FORMAT
	// [ ]  INITLIZIZE GFX RenderContext
	bool Graphics::CreateContext(HDC hDC)
	{
		hDeviceContext = hDC;

		const int pixelAttribs[] = {
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
			WGL_COLOR_BITS_ARB, cfg->GetGLSettings().colorBits,
			WGL_ALPHA_BITS_ARB, 8,
			WGL_DEPTH_BITS_ARB, cfg->GetGLSettings().depthBits,
			WGL_STENCIL_BITS_ARB, cfg->GetGLSettings().stencilBits,
			WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
			WGL_SAMPLES_ARB, 4,
			0
		};

		int pixelFormatID; UINT numFormats;
		const bool status = wglChoosePixelFormatARB(hDeviceContext, pixelAttribs, NULL, 1, &pixelFormatID, &numFormats);

		if (status == false || numFormats == 0) {
			std::wstringstream ss;

			ss << L"Failed to choose Pixel Format " << std::endl
				<< "Reason: " << std::endl
				<< "numFormats: " << numFormats << "\tpixelFormatID: " << pixelFormatID << std::endl;

			LOG_ERROR(ss.str().c_str());
			return false;
		}

		PIXELFORMATDESCRIPTOR PFD;
		DescribePixelFormat(hDeviceContext, pixelFormatID, sizeof(PFD), &PFD);
		SetPixelFormat(hDeviceContext, pixelFormatID, &PFD);

		const int major_min = 4, minor_min = 0;
		const int contextAttribs[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, major_min,
			WGL_CONTEXT_MINOR_VERSION_ARB, minor_min,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			//		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
					0
		};

		hRenderContext = wglCreateContextAttribsARB(hDeviceContext, 0, contextAttribs);
		if (hRenderContext == NULL) {
			LOG_ERROR(L"Failed to Create OpenGL Render Context");
			return false;
		}

		return true;
	}

	bool Graphics::SetSwapInterval(int interval)
	{
		PFNWGLSWAPINTERVALEXTPROC swapProc;
		swapProc = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglGetSwapIntervalEXT");
		swapProc(interval);
		return true;
	}

	// MAKE CONTEXT CURRENT
		// [X] DESTROYS PROXY WINDOW
		// [X] MAKES GFX CONTEXT CURRENT
	bool Graphics::MakeContextCurrent()
	{
		if (proxyHDC != nullptr)
			if (!DestroyProxyContext()) {
				LOG_ERROR(L"Could Not Destroy Proxy Context");
				return false;
			}
		if (!wglMakeCurrent(hDeviceContext, hRenderContext))
		{
			LOG_ERROR(L"could not Update OpenGL render Context.");
			return false;
		}
		return true;
	}

	bool Graphics::DestroyProxyContext()
	{
		if (!wglMakeCurrent(NULL, NULL)) {
			LOG_ERROR(L"Could Not Remove Current Context.");
			return false;
		}
		if (!wglDeleteContext(proxyRC)) {
			LOG_ERROR(L"Could Not Delete Proxy Render Context.");
			return false;
		}
		ReleaseDC(proxyHWND, proxyHDC);
		if (!DestroyWindow(proxyHWND)) {
			LOG_ERROR(L"Could Not Destroy Proxy HWND.");
			return false;
		}
		proxyHWND = nullptr;
		proxyHDC = nullptr;
		proxyRC = nullptr;
		return true;
	}

	void Graphics::Update(float dt)
	{
		LOG(L"Update");
	}

	void Graphics::Render()
	{
		// CLEAR
		LOG(L"Render");

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//// DRAW
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


	}

	HDC Graphics::GetDeviceContext()
	{
		return hDeviceContext;
	}

	HGLRC Graphics::GetRenderContext()
	{
		return hRenderContext;
	}

	void Graphics::ProcessEvent(Event* ev)
	{
		// 
		WindowResizeEvent* wev = (WindowResizeEvent*)ev;
		if (wev != nullptr) {
			Resize(wev->GetWidth(), wev->GetHeight());
		}
		ev->Handle();
		delete ev;
		pEvents->pop();
	}

	void Graphics::Resize(int nWidth, int nHeight)
	{
		glViewport(0, 0, nWidth, nHeight);
	}
}
