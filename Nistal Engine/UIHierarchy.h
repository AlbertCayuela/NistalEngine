#ifndef __UIHIERARHCY_H__
#define __UIHIERARCHY_H__

#include "Module.h"
#include "Application.h"	
#include "Globals.h"
#include "UIWindow.h"

#include <vector>


class UIHierarchy : public UIWindow
{
public:
	UIHierarchy();
	~UIHierarchy();


	bool Start();
	void Draw();
	bool CleanUp();
	void SetHierarchy(GameObject* root);
	void SetPos();

private:
	uint counter = -1;

};

#endif 
