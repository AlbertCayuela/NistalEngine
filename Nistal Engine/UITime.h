#ifndef __UITIME_H__
#define __UITIME_H__

#include "Module.h"
#include "Application.h"
#include "UIWindow.h"

class UITime : public UIWindow
{
public:
	UITime();
	~UITime();

	bool Start();
	void Draw();
	bool CleanUp();

};

#endif // !__UITIME_H__
