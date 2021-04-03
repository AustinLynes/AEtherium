#include "Application.h"


Application::Application()
{
    window = new Window(&config);
    gfx = new Graphics();
}

Application::~Application()
{
    delete window;
    delete gfx;
}

bool Application::Init()
{
    if (!gfx->CreateDevice(&config)) {
        Debugger::LogError("Could Not Create Device Context. Exiting.");
        return false;
    }
    
    if (!window->Create(L"Ætherium Engine")) {
        return false;
    }

    if (!gfx->CreateContext(GetDC(window->GetWindowHandle()))) {
        LOG_ERROR(L"Could Not Create Graphics Context.");
        return false;
    }

    if (!gfx->MakeContextCurrent()) {
        LOG_ERROR(L"Could Not Set Device Context to Current");
        return false;
    }

    // SCENE MANAGEMENT
    if (!gfx->InitilizeScene()) {
        LOG_ERROR(L"Could Not Load Scene Information.");
        return false;
    }


    window->Show(SW_SHOWMAXIMIZED);
    
    return true;
}

int Application::Run()
{

    while (true) {

        if(const auto eCode = window->ProcessMessages()) {
            return *eCode;
        }

        // UPDATE 
        gfx->Update(0.4f);

        // RENDER 
        gfx->Render();
    }

}
