#include "Application.h"
#include "GameObject.h"
#include "GOMaterial.h"
#include "GOMesh.h"
#include "GOTransform.h"

GameObject::GameObject(GameObject* parent, const char* name)
{
	this->parent = parent;
	this->name = name;
	LOG("created a new GameObject");
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
		component = new GOMaterial(this);
		break;
	case(GOCOMPONENT_TYPE::MESH):
		component = new GOMesh(this);
		break;
	case(GOCOMPONENT_TYPE::TRANSFORM):
		component = new GOTransform(this);
		break;
	default:
		break;
	}

	return component;
}

GOComponent* GameObject::GetComponent(GOCOMPONENT_TYPE type)
{
	return nullptr;
}
