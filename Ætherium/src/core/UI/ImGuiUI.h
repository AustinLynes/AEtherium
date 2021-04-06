#pragma once
#include <vendor/imgui/imgui_impl_glfw.h>
#include <vendor/imgui/imgui_impl_opengl3.h>
#include <vendor/imgui/imgui_internal.h>

#include <vector>

namespace UI
{
    class Window {
    public:
        virtual void Update() = 0;
        void Show();
        void Hide();
    protected:
        bool Begin(const char* title);
        void End();
        bool show = true;
    };

    class WindowManager
    {
    public:
        WindowManager();
        ~WindowManager();
        virtual void Update();
        void AddWindow(UI::Window* newWin);
    private:

        std::vector<UI::Window*> windows;

        void ShowDockSpace(bool* p_open);

        void Setstyle();

        void UpdateWindows();
        void DeleteWindows();
    };
};

