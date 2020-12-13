#ifndef __UIASSETS_H__
#define __UIASSETS_H__

#include "Module.h"
#include "Application.h"	
#include "Globals.h"
#include "UIWindow.h"

#include <vector>


class UIAssets : public UIWindow
{
public:
	UIAssets();
	~UIAssets();


	bool Start();
	void Draw();
	bool CleanUp();
	void SetPos();

private:
	uint counter = -1;

};

#endif 

