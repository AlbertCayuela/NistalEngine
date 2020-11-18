#pragma once
#include "Module.h"
#include "Globals.h"


class ModuleImporter : public Module
{
public:
	
	ModuleImporter(Application* app, bool start_enabled = true);
	~ModuleImporter();

	bool Start();
	bool Update();
	bool CleanUp();

	//import function is our current LoadMeshes
	bool SaveOwnFormat(modelData model, string name_to_file);
	bool LoadOwnFormat(string file_name);

	bool TextureSaving(string texture_name);

public:
	modelData data;
	bool loadOwnFormat = false;
	modelData modelOwnFormat;

};