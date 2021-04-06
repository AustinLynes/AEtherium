#pragma once
#include <Windows.h>
#include "Event.h"

class WindowEvent : public Event
{
public:
	// HWND handle to window sending the event
	WindowEvent(HWND hWnd);
	virtual ~WindowEvent() {}

	virtual unsigned int Category();

private:
	HWND hWnd;

};

class WindowResizeEvent : public WindowEvent {
public:
	WindowResizeEvent(HWND hWnd, int newWidth, int newHeight);
	~WindowResizeEvent();
	virtual const wchar_t* ToString() override;
	int GetWidth() { return width; }
	int GetHeight() { return height; }
private:
	wchar_t* buffer = nullptr;

	int width;
	int height;
};

