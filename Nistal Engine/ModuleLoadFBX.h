#pragma once

#include "Module.h"
#include "Globals.h"
#include <map>
#include "GameObject.h"
#include "Glew/include/glew.h"
#include <vector>
#include "MathGeoLib/include/Math/float3.h"
#include "Assimp/include/vector3.h"


class GameObject;
class aiScene;
class aiMesh;

struct modelData {

public:
	uint id_index = 0u; //index in VRAM
	uint num_index = 0u;
	uint* indices = nullptr;

	uint id_vertex = 0u; //unique vertex in VRAM
	uint num_vertex = 0u;
	float* vertices = nullptr;

	uint id_normals = 0u;
	uint num_normals = 0u;
	aiVector3D* normals = nullptr;

	uint num_faces = 0u;
	float3* faces_normals = nullptr;
	float3* face_middle = nullptr;

	//texture
	bool has_texture = false;
	GLuint texture;

	uint id_uvs = 0u;
	uint num_uvs = 0u;
	float* uvs = nullptr;

	uint num_uvs_channels = 0u;
	uint channel_buffer_size = 0u;

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

	bool LoadFBX(const char* file_path);
	void AddBuffers();
	//void DrawFBX(modelData model);
	void LoadMeshes(const aiScene* scene, GameObject* game_object, const char* file_path);
	void LoadIndices(aiMesh* scene);
	void DrawNormals(modelData model);
	void DrawVertexNormals(modelData model);
	void LoadTexture(const char* texture_path);

public:

	const char* path;
	const char* texture_path;
	const aiScene* scene;

	JSON_Object* model_node = nullptr;
	JSON_Object* texture_node = nullptr;

	aiMesh* mesh;
	aiMesh* new_mesh;
	modelData model;
	int texture_height;
	int texture_width;

	GLubyte* image = nullptr;
	GLint LOD = 0; //level of detail

	//GameObject* game_object = new GameObject(nullptr);
	GameObject* new_go;

	uint texture_id;

	//std::vector<GOMesh*> meshes;
	bool all_fbx_loaded = false;
};