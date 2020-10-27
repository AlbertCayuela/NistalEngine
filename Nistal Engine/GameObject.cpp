#include "GameObject.h"

GameObject::GameObject(GameObject* parent)
{
	this->parent = parent;
}

GameObject::~GameObject()
{
}

void GameObject::Update(float dt)
{
}

GOComponent* GameObject::AddComponent(GOCOMPONENT_TYPE type)
{
	return nullptr;
}

GOComponent* GameObject::GetComponent(GOCOMPONENT_TYPE type)
{
	return nullptr;
}
