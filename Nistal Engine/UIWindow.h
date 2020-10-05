#ifndef __UIWINDOW_H__
#define __UIWINDOW_H__

#include "Application.h"
#include "Globals.h"
#include "SDL/include/SDL.h"
class UIWindow
{
public:
	UIWindow();
	virtual ~UIWindow();

	virtual void Active();
	virtual bool IsActive();
	virtual void Draw() = 0;


public:
	bool is_on = false;
};

#endif 