#include "WindowEvents.h"

WindowEvent::WindowEvent(HWND hWnd) 
{
	handled = false;
}

unsigned int WindowEvent::Category()
{
	return  EventCategory::WINDOW | EventCategory::APPLICATION | EventCategory::GRAPHICS;
}


WindowResizeEvent::WindowResizeEvent(HWND hWnd, int newWidth, int newHeight) : WindowEvent(hWnd), width(newWidth), height(newHeight)
{
}

WindowResizeEvent::~WindowResizeEvent()
{
	delete buffer;
}

const wchar_t* WindowResizeEvent::ToString()
{
	std::wstringstream ss;
	ss << L"Window ResizeEvent"<<std::endl 
		<< L"new width: " << width <<std::endl
		<< L"new height: " << height <<'\0';
	int size = wcslen(ss.str().c_str()) + 1;
	buffer = new wchar_t[size];

	wcscpy_s(buffer, size, ss.str().c_str());
	
	return buffer;
}
