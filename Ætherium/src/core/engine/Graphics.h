#pragma once
#include <app/Config.h>
#include <core/debug/Debugger.h>


#include <Windows.h>
#include <comdef.h>

// OpenGL
#include <glad/glad.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <gl/glext.h>
#include <gl/wglext.h>
#include <queue>

#include <core/events/Event.h>
namespace Ætherium {
	using namespace Debug;

	class Graphics
	{
	public:
		Graphics(std::queue<Event*>* events);
		~Graphics();
	
		// CREATION
		bool CreateDevice(Config* cfg);

		bool CreateContext(HDC hDC);
		bool SetSwapInterval(int interval);
		bool MakeContextCurrent();
		bool DestroyProxyContext();

		bool InitilizeScene();
		void Update(float dt);
		void Render();

		HDC GetDeviceContext();
		HGLRC GetRenderContext();

		void ProcessEvent(Event* event);
		void Resize(int nWidth, int nHeight);
	private:
		bool InitLoaders();
		//wglext function pointers
		PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
		PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;

		HDC hDeviceContext;
		HGLRC hRenderContext;
	
		Config* cfg;

		// ptr to events queue in application
		std::queue<Event*>* pEvents;

		// proxy setup 
		HWND proxyHWND;
		HDC proxyHDC;
		HGLRC proxyRC;
	};
}

