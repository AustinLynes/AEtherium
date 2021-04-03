#pragma once
#include "BaseWindow.h"
#include <windowsx.h>
#include <core/engine/Graphics.h>
#include <core/debug/Debugger.h>

// STD includes ---> move to PCH --> or logger...?
#include <optional>

#include <comdef.h>


class Window : public BaseWindow<Window>
{
public:
	Window(Config* cfg);
	~Window();
	
	// Inherited via BaseWindow
	virtual bool Create(PCWSTR lpWindowName) override;
	
	// Message Pump
	std::optional<int> ProcessMessages();
	
	void Show(int nCmd);

	// Inherited via BaseWindow
	virtual LRESULT HandleMessages(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	virtual PCWSTR ClassName() override;


private:
	void RegisterMClass();
	Config* cfg;
};

