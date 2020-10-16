#pragma once

#include "Module.h"
#include "Globals.h"


struct vertexData {

	uint id_index = 0; //index in VRAM
	uint num_index = 0;
	uint* index = nullptr;

	uint id_vertex = 0; //unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;
};

class ModuleLoadFBX : public Module
{
public:

	ModuleLoadFBX(Application* app, bool start_enabled = true);
	~ModuleLoadFBX();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	bool LoadFBX(const char* path);
	void DrawFBX(vertexData model);

public:

	const char* path;

	JSON_Object* model_node = nullptr;
	aiMesh* mesh;
	aiMesh* new_mesh;
	vertexData model;
};