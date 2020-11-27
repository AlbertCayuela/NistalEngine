#ifndef __UILOAD_H__
#define __UILOAD_H__

#include "Module.h"
#include "Application.h"
#include "UIWindow.h"

class UILoad : public UIWindow
{
public:
	UILoad();
	~UILoad();

	bool Start();
	void Draw();
	bool CleanUp();

	void SetPos();
};

#endif // !__UILOAD_H__
