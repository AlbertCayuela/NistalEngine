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
	update_status Update(float dt);

	uint Find(const char* file_in_assets) const;
	uint ImportFile(const char* new_file_in_assets);
	uint GenerateNewUUID();
	uint GenerateTimeStamp();
	Resource* RequestResource(uint uuid);
	Resource* CreateNewResource(RESOURCE_TYPE type, uint uuid, std::string meta_path);

	void GenerateMeta(const char* path, RESOURCE_TYPE type);
	void GenerateMissingMetas();
	void GenerateLibaryResources();


public:

	std::vector<std::string> mesh_files;
	std::vector<std::string> mesh_dirs;
	std::vector<std::string> material_files;
	std::vector<std::string> material_dirs;
	std::vector<std::string> library_mesh_files;
	std::vector<std::string> library_mesh_dirs;
	std::vector<std::string> library_material_files;
	std::vector<std::string> library_material_dirs;
	Timer timer;

private:

	std::map<uint, Resource*> resources;
	LCG lcg;
};

#endif
