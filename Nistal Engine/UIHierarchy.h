#pragma once
#ifndef __UIHIERARCHY_H__
#define __UIHIERARCHY_H__


#include "Module.h"
#include "Application.h"	
#include "Globals.h"
#include "UIWindow.h"
#include "SDL/include/SDL.h"
#include "imGUI\imgui.h"

class UIHierarchy : public UIWindow
{
public:
	UIHierarchy();
	~UIHierarchy();


	bool Start();
	void Draw();
	bool CleanUp();

private:

};

#endif 
