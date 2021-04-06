#pragma once
#include <core/window/Window.h>
#include <core/engine/Graphics.h>
#include <queue>
#include <core/events/WindowEvents.h>

// IMGUI -------------
#include <core/UI/ImGuiUI.h>
///--------------
namespace Ætherium {

	class Application : public UI::WindowManager
	{
	public:
		Application();
		~Application();

		virtual void Update() override;
		bool ShouldClose() { return mainWindow.ShouldClose(); }
	private:
		Graphics* gfx;
		Window mainWindow;
		Config config;

		// for simplisity sake...
		std::queue<Event*> events;
	};
}

