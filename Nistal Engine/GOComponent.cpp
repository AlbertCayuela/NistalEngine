#include "GOComponent.h"


GOComponent::GOComponent(GameObject* game_object)
{
}

GOComponent::~GOComponent()
{
}

void GOComponent::Update(float dt)
{
}

bool GOComponent::Enable() //TODO CHECK THESE FUNCTIONS
{
	active = true;

	return active;
}

bool GOComponent::Disable()
{
	active = false;

	return active;
}
