#include <app/Application.h>

#ifdef WIN32
int APIENTRY WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR nCmdLine, _In_ int nCmdShow) {
	Application app;
	if (!app.Init()) {
		return -1;
	}
	int eCode = app.Run();
	return eCode;
}
#else 
#error "Ætherium only supports Windows at the moment please check back later to see if your architecture will be added. for more information email me at austinlynes2012@gmail.com"
#endif