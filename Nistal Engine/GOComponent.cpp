#include "GOComponent.h"

GOComponent::GOComponent()
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
