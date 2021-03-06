#pragma once
#ifndef __UIINSPECTOR_H__
#define __UIINSPECTOR_H__


#include "Module.h"
#include "Application.h"	
#include "Globals.h"
#include "UIWindow.h"
#include "SDL/include/SDL.h"
#include "imGUI\imgui.h"

class UIInspector : public UIWindow
{
public:
	UIInspector();
	~UIInspector();


	bool Start();
	void Draw ();
	bool CleanUp();

	void LoadInspectoData(GameObject* GO);
	void SetPos();

	void UseGuizmo(GameObject* selected_go);

	bool mesh_exists = false;

private:

	const char* inspector_name;
	float3 rot = float3::zero;
};

#endif 
