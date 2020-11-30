#include "Application.h"
#include "ModuleResourceManager.h"

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
	return uint();
}

uint ModuleResourceManager::GenerateNewUUID()
{
	return uint();
}

Resource* ModuleResourceManager::RequestResource(uint uuid)
{
	return nullptr;
}

Resource* ModuleResourceManager::CreateNewResource(RESOURCE_TYPE type, uint uuid, const char* path)
{
	return nullptr;
}
