#include "Application.h"

#define SCR_WIDTH 1280
#define SCR_HEIGHT 720

namespace Ætherium {


	Application::Application() : mainWindow{ SCR_WIDTH, SCR_HEIGHT }
	{

		ImGui_ImplGlfw_InitForOpenGL(mainWindow.GetRawWindow(), true);
		const char* glsl_version = "#version 460 core";
		ImGui_ImplOpenGL3_Init(glsl_version);
	}

	Application::~Application()
	{
		ImGui_ImplOpenGL3_Shutdown();
	}

	void Application::Update()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		UI::WindowManager::Update();

		ImGuiIO& io = ImGui::GetIO(); (void)io;

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}



		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		mainWindow.Draw();
	}


}
