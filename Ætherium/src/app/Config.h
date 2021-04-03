#pragma once
#include <windows.h>

////*********** WINDOW ***********/////
#define DEFAULT_WINDOW_WIDTH	1280
#define DEFAULT_WINDOW_HEIGHT	720
#define DEFAULT_WINDOW_POSITION_X()	GetSystemMetrics(SM_CXSCREEN) / 2	- DEFAULT_WINDOW_WIDTH / 2
#define DEFAULT_WINDOW_POSITION_Y()	GetSystemMetrics(SM_CYSCREEN) / 2 - DEFAULT_WINDOW_HEIGHT / 2
#define DEFAULT_WINDOW_FULLSCREEN	FALSE
#define DEFAULT_WINDOW_VSYNC	TRUE
#define DEFAULT_WINDOW_MAXFPS 75
#define DEFAULT_WINDOW_CLASS_NAME L"AEtherium_Engine_Main_Window"
#define DEFAULT_WINDOW_TITLE L"Ætherium Engine"
////*********** /WINDOW ***********/////

////*********** OPENGL ***********/////
#define DEFAULT_OPENGL_COLOR_BITS 32
#define DEFAULT_OPENGL_DEPTH_BITS 24
#define DEFAULT_OPENGL_STENCIL_BITS 8
#define DEFAULT_OPENGL_VERSION_MAJOR 4
#define DEFAULT_OPENGL_VERSION_MINOR 6
////*********** /OPENGL ***********/////

class Setting {
public:
	virtual void Reset() = 0;
};

struct Window_Settings : public Setting {
public:
	int	x = DEFAULT_WINDOW_POSITION_X();
	int	y = DEFAULT_WINDOW_POSITION_Y();
	int	width = DEFAULT_WINDOW_WIDTH;
	int	height = DEFAULT_WINDOW_HEIGHT;
	bool fullscreen = DEFAULT_WINDOW_FULLSCREEN;
	bool vSync = DEFAULT_WINDOW_VSYNC;
	int	maxFPS = DEFAULT_WINDOW_MAXFPS;
	const wchar_t*	WCLASS_NAME = DEFAULT_WINDOW_CLASS_NAME;
	const wchar_t* WTITLE = DEFAULT_WINDOW_TITLE;

	virtual void Reset() override {
		x = DEFAULT_WINDOW_POSITION_X();
		y = DEFAULT_WINDOW_POSITION_Y();
		width = DEFAULT_WINDOW_WIDTH;
		height = DEFAULT_WINDOW_HEIGHT;
		fullscreen = DEFAULT_WINDOW_FULLSCREEN;
		vSync = DEFAULT_WINDOW_VSYNC;
		maxFPS = DEFAULT_WINDOW_MAXFPS;
		WCLASS_NAME = DEFAULT_WINDOW_CLASS_NAME;
		WTITLE = DEFAULT_WINDOW_TITLE;
	}
};

struct OpenGL_Settings : public Setting {
public:
	int colorBits = DEFAULT_OPENGL_COLOR_BITS;
	int depthBits = DEFAULT_OPENGL_DEPTH_BITS;
	int stencilBits = DEFAULT_OPENGL_STENCIL_BITS;
	int major = DEFAULT_OPENGL_VERSION_MAJOR;
	int minor = DEFAULT_OPENGL_VERSION_MINOR;

	virtual void Reset() override {
		colorBits = DEFAULT_OPENGL_COLOR_BITS;
		depthBits = DEFAULT_OPENGL_DEPTH_BITS;
		stencilBits = DEFAULT_OPENGL_STENCIL_BITS;
		major = DEFAULT_OPENGL_VERSION_MAJOR;
		minor = DEFAULT_OPENGL_VERSION_MINOR;
	}
};


/// <summary>
/// Application config. can be changed. if reset is needed 
/// </summary>
struct Config {
public:
	Window_Settings GetWindowSettings() const { return window; }
	OpenGL_Settings GetGLSettings() const { return opengl; }

private:
	Window_Settings window;
	OpenGL_Settings opengl;
};

