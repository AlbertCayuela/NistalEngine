#pragma once

#include "Module.h"
#include "Globals.h"

#include "Glew/include/glew.h"

class ModuleTexture : public Module
{
public:

	ModuleTexture(Application* app, bool start_enabled = true);
	~ModuleTexture();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	bool LoadTexture(modelData model, const char* path);
	void LoadUVs(modelData* model, aiMesh* mesh);
	void LoadMaterials(const aiScene* scene, aiMesh* mesh, modelData* model);

public:
	JSON_Object* texture_node = nullptr;
	const char* texture_path = nullptr;

	GLubyte HouseImage[CHECKERS_WIDTH][CHECKERS_HEIGHT][4];

};