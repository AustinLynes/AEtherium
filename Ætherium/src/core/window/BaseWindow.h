#pragma once
#include <app/Config.h>

#include <iostream>
template<class T>
class BaseWindow {
public:
	BaseWindow() : hWnd(NULL) {}
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		T* pThis = nullptr;

		if (uMsg == WM_NCCREATE) {
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
			pThis = (T*)pCreate->lpCreateParams;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
			if(pThis)
			pThis->hWnd = hWnd;

		}
		else {
			pThis = (T*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		}

		if (pThis != nullptr) {
			return pThis->HandleMessages(uMsg, wParam, lParam);
		}
		else {
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}

	// virtual create function to allow user to create any winAPI window for any purpose
	virtual bool Create(PCWSTR lpWindowName) = 0;

	HWND GetWindowHandle() { return hWnd; }
	virtual PCWSTR ClassName() = 0;

protected:
	virtual LRESULT HandleMessages(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

	DWORD dwStyle = NULL;
	DWORD dwExStyle = NULL;
	HWND hWnd;
};