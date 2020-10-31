#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <vector>
#include <string>
#include "Globals.h"

enum GOCOMPONENT_TYPE
{
	NONE = 0,
	TRANSFORM,
	MESH,
	MATERIAL
};

class GOComponent;
class GOMaterial;
class GOMesh;
class GOTransform;

class GameObject 
{
public:

	GameObject(GameObject* parent, const char* name);
	~GameObject();
	void Update(float dt);
	GOComponent* AddComponent(GOCOMPONENT_TYPE type, const char* name);
	GOComponent* GetComponent(GOCOMPONENT_TYPE type);
	void GetNames(const char* name);

	std::string name;
	std::string path;
	std::string ui_name;
	GOMaterial* material = nullptr;
	GOMesh* mesh = nullptr;
	GOTransform* transform = nullptr;
	bool has_mesh = false;
	bool has_material = false;
	bool active = true;
	bool selected = false;
	std::vector<GOComponent*> go_components;
	std::vector<GameObject*> children;
	GameObject* parent = nullptr;
};

#endif