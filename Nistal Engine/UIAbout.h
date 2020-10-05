#ifndef __UIABOUT_H__
#define __UIABOUT_H__


#include "Module.h"
#include "Application.h"	
#include "Globals.h"
#include "UIWindow.h"
#include "SDL/include/SDL.h"
#include "imGUI\imgui.h"

#include <vector>


class UIAbout : public UIWindow
{
public:
	UIAbout();
	~UIAbout();


	bool Start();
	void Draw();
	bool CleanUp();

private:

};

#endif 
