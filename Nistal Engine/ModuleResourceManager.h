#ifndef __MODULERESOURCEMANAGER_H__
#define __MODULERESOURCEMANAGER_H__

#include "Module.h"
#include "Resource.h"
#include "MathGeoLib/include/Algorithm/Random/LCG.h"

class ModuleResourceManager : public Module {


public:

	ModuleResourceManager(Application* app, bool start_enabled = true);
	~ModuleResourceManager();

	bool Start();

	uint Find(const char* file_in_assets) const;
	uint ImportFile(const char* new_file_in_assets);
	uint GenerateNewUUID();
	Resource* RequestResource(uint uuid);
	Resource* CreateNewResource(RESOURCE_TYPE type, const char* path);

	void GenerateMeta(const char* path, RESOURCE_TYPE type);

public:

	std::vector<std::string> mesh_files;
	std::vector<std::string> mesh_dirs;
	std::vector<std::string> material_files;
	std::vector<std::string> material_dirs;

private:

	std::map<uint, Resource*> resources;
	LCG lcg;
};

#endif
