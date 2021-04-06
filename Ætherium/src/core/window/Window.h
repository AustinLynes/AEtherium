#pragma once
#include <core/engine/Graphics.h>
#include <core/debug/Debugger.h>
#include <core/UI/ImGuiUI.h>

// STD includes ---> move to PCH --> or logger...?
#include <optional>

#include <comdef.h>
#include <queue>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Ætherium {

	class Window {
	public:
		Window(int width, int height);
		~Window();

		void Draw();
		bool ShouldClose();
		int GetWidth();
		int GetHeight();
		void Resize(int width, int height);
		GLFWwindow* GetRawWindow();
	private:
		int width;
		int height;
		GLFWwindow* window;

	};

}

