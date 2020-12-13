#pragma once
#include "Module.h"
#include "Globals.h"
#include "GameObject.h"
#include "Resource.h"
#include "Glew/include/glew.h"
#include <vector>
#include "MathGeoLib/include/Math/float3.h"
#include "Assimp/include/vector3.h"
#include "MathGeoLib/include/Math/Quat.h"


class GameObject;
class Resource;
class aiScene;
class aiMesh;
class aiNode;

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

	uint nums_uvs_channels = 0u;
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

	bool LoadFBX(const char* file_path, GameObject* parent = nullptr);
	void AddBuffers();
	void LoadMeshes(const aiScene* scene, aiNode* node, GameObject* game_object, const char* file_path);

	void LoadIndices(aiMesh* scene);
	void LoadTexture(const char* texture_path);
	void LoadMaterial(GameObject* game_object);
	void LoadVertices();

	void DrawNormals(modelData model);
	void DrawVertexNormals(modelData model);

	void Unparent();

public:

	const char* model_path;
	const char* texture_path;
	const aiScene* scene;

	JSON_Object* model_node = nullptr;
	JSON_Object* texture_node = nullptr;

	aiMesh* mesh;
	aiMesh* new_mesh;
	modelData model;
	int texture_height;
	int texture_width;
	uint textures_num;
	std::string go_name;

	GLubyte* image = nullptr;
	GLint LOD = 0; //level of detail

	GameObject* new_go;

	uint texture_id;

	bool all_fbx_loaded = false;
	GameObject* new_parent = nullptr;
	bool parent = false;

	Resource* new_resource = nullptr;

};