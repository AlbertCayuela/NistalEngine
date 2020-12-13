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

public: 
	
	bool files_checked = false;
	std::vector<std::string> files_list;
	std::vector<std::string> dir_list;

	std::string scene_selected;
	bool scene_select = false;
};

#endif // !__UILOAD_H__
