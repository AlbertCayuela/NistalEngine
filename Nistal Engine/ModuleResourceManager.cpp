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

bool ModuleResourceManager::Start()
{
	App->file_system->DiscoverFiles("Models/", mesh_files, mesh_dirs);

	for (std::vector<string>::iterator i = mesh_files.begin(); i != mesh_files.end(); i++) 
	{
		LOG("mesh detected: %s", (*i).c_str());
	}


	return true;
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

void ModuleResourceManager::GenerateMeta(const char* path, RESOURCE_TYPE type)
{
	std::string meta_path = path;
	meta_path = meta_path + ".meta";

	if (!App->file_system->Exists(meta_path.c_str())) 
	{
		JSON_Value* root = json_value_init_object();
		JSON_Object* obj = json_value_get_object(root);

		json_object_set_number(obj, "Type", type);
		json_object_set_number(obj, "UUID", 0); //TODO set correct uuid
		json_object_set_number(obj, "Time", 0); //TODO set correct time

		json_serialize_to_file_pretty(root, meta_path.c_str());
	}

}

