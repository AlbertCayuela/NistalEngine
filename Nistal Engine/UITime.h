#ifndef __UITIME_H__
#define __UITIME_H__

#include "Module.h"
#include "Application.h"
#include "UIWindow.h"
#include "Timer.h"

class UITime : public UIWindow
{
public:
	UITime();
	~UITime();

	bool Start();
	void Draw();
	bool CleanUp();

	void SetPos();

public:

	Timer timer;
};

#endif // !__UITIME_H__
