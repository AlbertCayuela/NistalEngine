#ifndef __UICONSOLE_H__
#define __UICONSOLE_H__

#include "Module.h"
#include "Application.h"
#include "UIWindow.h"

class UIConsole : public UIWindow
{
public:
	UIConsole();
	~UIConsole();

	bool Start();
	void Draw();
	bool CleanUp();

	void SetPos();
};

#endif // !__UICONSOLE_H__
