#pragma once
#include <core/window/Window.h>
#include <core/engine/Graphics.h>

class Application
{
public:
	Application();
	~Application();

	bool Init();
	int Run();

private:

	Window* window;
	Graphics* gfx;

	Config config;
};

