#pragma once
#ifndef __UIINSPECTOR_H__
#define __UIINSPECTOR_H__


#include "Module.h"
#include "Application.h"	
#include "Globals.h"
#include "UIWindow.h"
#include "SDL/include/SDL.h"
#include "imGUI\imgui.h"

class UIInspector : public UIWindow
{
public:
	UIInspector();
	~UIInspector();


	bool Start();
	void Draw ();
	bool CleanUp();

private:

};

#endif 
