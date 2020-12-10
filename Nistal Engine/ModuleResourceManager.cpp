#include "Application.h"
#include "ModuleResourceManager.h"
#include "Resource.h"
#include "ResourceMesh.h"
#include "ResourceMaterial.h"


ModuleResourceManager::ModuleResourceManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleResourceManager::~ModuleResourceManager()
{
}

uint ModuleResourceManager::Find(const char* file_in_assets) const
{
	return uint();
}

uint ModuleResourceManager::ImportFile(const char* new_file_in_assets)
{
	uint ret = 0;
	

	return ret;
}

uint ModuleResourceManager::GenerateNewUUID()
{
	return lcg.Int();
}

Resource* ModuleResourceManager::RequestResource(uint uuid)
{
	return nullptr;
}

Resource* ModuleResourceManager::CreateNewResource(RESOURCE_TYPE type, const char* path)
{
	Resource* ret = nullptr;
	uint uuid = GenerateNewUUID();

	switch (type) 
	{
	case RESOURCE_MESH:
		ret = (Resource*) new ResourceMesh(uuid);
		break;
	case RESOURCE_MATERIAL:
		ret = (Resource*) new ResourceMaterial(uuid);
		break;
	}

	if (ret != nullptr)
		resources[uuid] = ret;

	return ret;
}
