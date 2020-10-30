#include "Application.h"
#include "GameObject.h"
#include "GOMaterial.h"
#include "GOMesh.h"
#include "GOTransform.h"

GameObject::GameObject(GameObject* parent, const char* name)
{
	this->parent = parent;
	this->name = name;
	AddComponent(GOCOMPONENT_TYPE::TRANSFORM);
	LOG("New GameObject created: %s", this->name.c_str());
}

GameObject::~GameObject()
{
}

void GameObject::Update(float dt)
{
}

GOComponent* GameObject::AddComponent(GOCOMPONENT_TYPE type)
{
	GOComponent* component = nullptr;

	switch (type)
	{
	case(GOCOMPONENT_TYPE::MATERIAL):
		material = new GOMaterial(this);
		component = material;
		break;
	case(GOCOMPONENT_TYPE::MESH):
		mesh = new GOMesh(this);
		component = mesh;
		has_mesh = true;
		break;
	case(GOCOMPONENT_TYPE::TRANSFORM):
		transform = new GOTransform(this);
		component = transform;
		break;
	default:
		break;
	}

	go_components.push_back(component);

	return component;
}

GOComponent* GameObject::GetComponent(GOCOMPONENT_TYPE type)
{
	return nullptr;
}
