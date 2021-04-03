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



class Graphics
{
public:
	Graphics();
	~Graphics();
	
	// CREATION
	bool CreateDevice(Config* cfg);

	bool CreateContext(HDC hDC);
	
	bool MakeContextCurrent();
	bool DestroyProxyContext();

	bool InitilizeScene();
	void Update(float dt);
	void Render();

	HDC GetDeviceContext();
	HGLRC GetRenderContext();

private:
	bool InitLoaders();
	//wglext function pointers
	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;

	HDC hDeviceContext;
	HGLRC hRenderContext;
	
	Config* cfg;

	// proxy setup 
	HWND proxyHWND;
	HDC proxyHDC;
	HGLRC proxyRC;
};

