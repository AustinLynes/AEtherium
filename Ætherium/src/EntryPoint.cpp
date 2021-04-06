
#include <app/Application.h>
#include <core/window/windows/Console.h>

//#if defined _MSC_VER && defined _DEBUG // major and minor number elements of the compiler's version number. && ARE IN DEBUG MODE
//#include <crtdbg.h>
////#define new new(_NORMAL_BLOCK, __FILE__, __LINE__);
//#define ENABLE_LEAK_DETECT() _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
//#else
//#define ENABLE_LEAK_DETECT()
//#endif

#ifdef WIN32
using namespace Ætherium;
using namespace UIWindow;
using namespace UI;
int main() {

	// LEAK DETECTION MODULE
	//ENABLE_LEAK_DETECT();
	//_CrtSetBreakAlloc(-1);

	Application app;
	app.AddWindow(new Console());
	while (!app.ShouldClose()) {
		app.Update();
	}
	return 0;
}
#else 
#error "Ætherium only supports Windows at the moment please check back later to see if your architecture will be added. for more information email me at austinlynes2012@gmail.com"
#endif