#ifndef __MODULERESOURCEMANAGER_H__
#define __MODULERESOURCEMANAGER_H__

#include "Module.h"
#include "Resource.h"
#include "MathGeoLib/include/Algorithm/Random/LCG.h"

class ModuleResourceManager : public Module {


public:

	ModuleResourceManager(Application* app, bool start_enabled = true);
	~ModuleResourceManager();

	uint Find(const char* file_in_assets) const;
	uint ImportFile(const char* new_file_in_assets);
	uint GenerateNewUUID();
	Resource* RequestResource(uint uuid);
	Resource* CreateNewResource(RESOURCE_TYPE type, const char* path);

private:

	std::map<uint, Resource*> resources;
	LCG lcg;
};

#endif
