#pragma once

#include "Module.h"
#include "Globals.h"
#include <map>
#include "GameObject.h"
#include "Glew/include/glew.h"

#define CHECKERS_WIDTH 64
#define CHECKERS_HEIGHT 64

class Texture;

struct modelData {

public:
	uint id_index = 0u; //index in VRAM
	uint num_index = 0u;
	uint* indices = nullptr;

	uint id_vertex = 0u; //unique vertex in VRAM
	uint num_vertex = 0u;
	float* vertices = nullptr;

	uint* id_normals = 0u;
	uint num_normals = 0u;
	aiVector3D* normals = nullptr;

	uint num_faces = 0u;
	float3* faces_normals = nullptr;
	float3* face_middle = nullptr;

	//texture
	/*uint id_uv = 0u;
	uint num_uv_components = 0u;
	float* uv_coord = nullptr;

	uint id_texture = 0u;*/
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
	void LoadMeshes(const aiScene* scene, GameObject* game_object);
	void LoadIndices(aiMesh* scene);
	void DrawNormals(modelData model);
	void DrawVertexNormals(modelData model);

public:

	const char* path;
	const aiScene* scene;

	JSON_Object* model_node = nullptr;
	aiMesh* mesh;
	aiMesh* new_mesh;
	modelData model;
	//TODO: FBX modelData array
	GLubyte* image = nullptr;
	GLint LOD = 0; //level of detail

	//TEXTURES
	GLubyte checkerImage[CHECKERS_WIDTH][CHECKERS_HEIGHT][4];

	GameObject* game_object = new GameObject(nullptr);
};