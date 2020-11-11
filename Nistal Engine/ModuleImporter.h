#pragma once
#include "Module.h"
#include "Globals.h"


class ModuleImporter : public Module
{
public:
	
	ModuleImporter(Application* app, bool start_enabled = true);
	~ModuleImporter();

	bool Start();
	bool CleanUp();

	//import function is our current LoadMeshes
	bool SaveData(modelData model, string file_name);
	bool LoadData();

public:
	modelData data;

};