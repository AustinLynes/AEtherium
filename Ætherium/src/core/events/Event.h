#pragma once
#include <sstream>

#define BIT(bit) (1<<bit)

enum EventCategory {
	NO_CATEGORY = 0,
	WINDOW		= BIT(0), // WINDOW level events include 
						  // CLOSE
						  // RESIZE 
	
	GRAPHICS	= BIT(1), // GRAPHICS level events include 
						  // DRAW 

	APPLICATION = BIT(2), // APPLICATION level events include

	//INPUT		= 1 << 2,
};


class Event {
public:
	virtual ~Event() {};
	virtual const wchar_t* ToString() = 0;
	
	void Handle() { handled = true; }

	virtual unsigned int Category() = 0; // 32 bits for manipulation
protected:
	bool handled;
};