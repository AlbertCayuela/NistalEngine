#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <vector>
#include <string>

enum GOCOMPONENT_TYPE
{
	NONE = 0,
	TRANSFORM,
	MESH,
	MATERIAL
};

class GOComponent;

class GameObject 
{
public:

	GameObject(GameObject* parent = nullptr);
	~GameObject();
	void Update(float dt);
	GOComponent* AddComponent(GOCOMPONENT_TYPE type);
	GOComponent* GetComponent(GOCOMPONENT_TYPE type);

	std::string name;

private:

	GameObject* parent = nullptr;
	std::vector<GOComponent*> go_components;
	std::vector<GameObject*> children;

};

#endif