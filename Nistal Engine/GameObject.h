#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <vector>
#include <string>
#include "Globals.h"
#include "Parson/parson.h"
#include "MathGeoLib/include/MathGeoLib.h"

enum GOCOMPONENT_TYPE
{
	NONE = 0,
	TRANSFORM,
	MESH,
	MATERIAL,
	CAMERA,
	AUDIO_SOURCE,
	AUDIO_LISTENER,
};

class GOComponent;
class GOMaterial;
class GOMesh;
class GOTransform;
class GOCamera;
class GOAudioSource;
class GOAudioListener;

class GameObject 
{
public:

	GameObject(GameObject* parent, const char* name);
	~GameObject();
	void Update(float dt);
	GOComponent* AddComponent(GOCOMPONENT_TYPE type, const char* name);
	GOComponent* GetComponent(GOCOMPONENT_TYPE type);
	void GetNames(const char* name);
	u32 GenerateUUID();

	void AddBoundingBox();
	void DrawBoundingBox();

	void DeleteGameObjects();

	std::string name;
	std::string path;
	std::string ui_name;
	GOMaterial* material = nullptr;
	GOMesh* mesh = nullptr;
	GOTransform* transform = nullptr;
	GOCamera* camera = nullptr;
	GOAudioSource* audio_source = nullptr;
	GOAudioListener* audio_listener = nullptr;
	bool has_mesh = false;
	bool has_material = false;
	bool has_bbox = false;
	bool has_camera = false;
	bool has_audio_source = false;
	bool has_audio_listener = false;
	bool active = true;
	bool selected = false;
	std::vector<GOComponent*> go_components;
	std::vector<GameObject*> children;
	GameObject* parent = nullptr;
	math::AABB bbox;
	math::OBB obb_box;
	LCG lcg;
	uint uuid = 0;
	uint parent_uuid = 0;

public:
	void SaveInfoGameObject(GameObject* go, JSON_Array* json_array);
	void LoadInfoGameObject(GameObject* game_object, JSON_Object* obj);

	JSON_Value* components;
	JSON_Array* componentsObj;
};

#endif