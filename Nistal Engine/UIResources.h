#ifndef __UIRESOURCES_H__
#define __UIRESOURCES_H__

#include "Module.h"
#include "Application.h"	
#include "Globals.h"
#include "UIWindow.h"

#include <vector>


class UIResources : public UIWindow
{
public:
	UIResources();
	~UIResources();


	bool Start();
	void Draw();
	bool CleanUp();
	void SetPos();

private:
	uint counter = -1;

};

#endif 
