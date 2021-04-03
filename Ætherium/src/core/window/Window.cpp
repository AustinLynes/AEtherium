#include "Window.h"

Window::Window(Config* cfg)
{
    this->cfg = cfg;
    this->RegisterMClass();
}

Window::~Window()
{
}

bool Window::Create(PCWSTR lpWindowName)
{
    RECT clientRect;
    clientRect.left =   cfg->GetWindowSettings().x;
    clientRect.top =    cfg->GetWindowSettings().y;
    clientRect.right =  cfg->GetWindowSettings().x + cfg->GetWindowSettings().width;
    clientRect.bottom = cfg->GetWindowSettings().y + cfg->GetWindowSettings().height;
    
    dwStyle = WS_OVERLAPPEDWINDOW;
    dwExStyle = WS_EX_OVERLAPPEDWINDOW;

    if (!AdjustWindowRectEx(&clientRect, dwStyle, FALSE, dwExStyle)) {
        return false;
    }

    DEVMODE deviceScreenSettings = { 0 };
    deviceScreenSettings.dmSize = sizeof(DEVMODE);
    deviceScreenSettings.dmPelsWidth =  cfg->GetWindowSettings().width;
    deviceScreenSettings.dmPelsHeight = cfg->GetWindowSettings().height;
    deviceScreenSettings.dmBitsPerPel = cfg->GetGLSettings().colorBits;
    deviceScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

    // CREATE DEVICE
    // [ ] INITILIZES GFX config
    // [ ] Queries wglext function pointers


    std::wstringstream ss;
    ss << cfg->GetWindowSettings().WTITLE << L"(" << cfg->GetWindowSettings().width << "x" << cfg->GetWindowSettings().height << L")" << std::endl;
    hWnd = CreateWindowExW(
        dwExStyle, 
        ClassName(), 
        ss.str().c_str(), 
        dwStyle, 
        clientRect.left, 
        clientRect.top, 
        clientRect.right - clientRect.left, 
        clientRect.bottom - clientRect.top,
        NULL, 
        NULL, 
        GetModuleHandle(NULL), 
        this
    );




    return true;
}

LRESULT Window::HandleMessages(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    
    case WM_SIZE:
    {
        int sizeX = GET_X_LPARAM(lParam);
        int sizeY = GET_Y_LPARAM(lParam);
        std::stringstream ss;
        ss << "width: " << sizeX << " height: " << sizeY << std::endl;
        LOG(ss.str().c_str());

        // send window resize event.
        // if :: event == windowEvent
        // resize in graphics
    }
        break;

    case WM_LBUTTONDOWN:
        LOG("LMB CLICKED");
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

}

std::optional<int> Window::ProcessMessages()
{
    MSG msg = {};

    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

        if (msg.message == WM_QUIT )
            return msg.wParam;

        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return {};
}

void Window::Show(int nCmd) {
    ShowWindow(hWnd, nCmd);
    UpdateWindow(hWnd);
}

PCWSTR Window::ClassName()
{
    return L"AEtherium_Engine_Main_Window"; // <---- CHANGE THIS
}

void Window::RegisterMClass()
{
    WNDCLASSEXW wndClass = { 0 };
    wndClass.cbSize = sizeof(WNDCLASSEXW);
    wndClass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
    wndClass.lpfnWndProc = WindowProc;
    wndClass.hInstance = GetModuleHandle(NULL);
    wndClass.lpszClassName = ClassName();

    RegisterClassExW(&wndClass);
}

