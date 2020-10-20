#pragma once

#include "Module.h"
#include "Globals.h"

struct modelData {

	uint id_index = 0u; //index in VRAM
	uint num_index = 0u;
	uint* index = nullptr;

	uint id_vertex = 0u; //unique vertex in VRAM
	uint num_vertex = 0u;
	float* vertex = nullptr;

	uint* id_normals = 0u;
	uint num_normals = 0u;
	aiVector3D* normals = nullptr;
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
	void AddFBX();
	void DrawFBX(modelData model);
	void DrawFaceNormals();
	void LoadMeshes(const aiScene* scene);
	void LoadIndices(aiMesh* scene);

public:

	const char* path;
	const aiScene* scene;

	JSON_Object* model_node = nullptr;
	aiMesh* mesh;
	aiMesh* new_mesh;
	modelData model;
};