#ifndef __UISAVE_H__
#define __UISAVE_H__

#include "Module.h"
#include "Application.h"
#include "UIWindow.h"

class UISave : public UIWindow
{
public:
	UISave();
	~UISave();

	bool Start();
	void Draw();
	bool CleanUp();

	void SetPos();
};

#endif // !__UISAVE_H__
