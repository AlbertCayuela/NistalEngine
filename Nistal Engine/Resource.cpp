#include "Resource.h"

Resource::Resource(uint uuid, RESOURCE_TYPE type)
{
}

Resource::~Resource()
{
}

RESOURCE_TYPE Resource::GetResourceType() const
{
    return RESOURCE_TYPE();
}

uint Resource::GetUUID() const
{
    return uint();
}

bool Resource::IsLoadedToMemory() const
{
    return false;
}

bool Resource::LoadToMemory()
{
    return false;
}

bool Resource::UnloadToMemory()
{
    return false;
}

uint Resource::CountReferences() const
{
    return uint();
}
