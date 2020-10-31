#include "Application.h"
#include "GameObject.h"
#include "GOMaterial.h"
#include "GOMesh.h"
#include "GOTransform.h"

GameObject::GameObject(GameObject* parent, const char* name)
{
	this->parent = parent;
	this->name = name;
	if (parent != nullptr)
		parent->children.push_back(this);
	AddComponent(GOCOMPONENT_TYPE::TRANSFORM, "transform");
	LOG("New GameObject created: %s", this->name.c_str());
}

GameObject::~GameObject()
{
}

void GameObject::Update(float dt)
{
}

GOComponent* GameObject::AddComponent(GOCOMPONENT_TYPE type, const char* name)
{
	GOComponent* component = nullptr;

	switch (type)
	{
	case(GOCOMPONENT_TYPE::MATERIAL):
		material = new GOMaterial(this, name);
		component = material;
		has_material = true;
		break;
	case(GOCOMPONENT_TYPE::MESH):
		mesh = new GOMesh(this, name);
		component = mesh;
		has_mesh = true;
		break;
	case(GOCOMPONENT_TYPE::TRANSFORM):
		transform = new GOTransform(this, name);
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
