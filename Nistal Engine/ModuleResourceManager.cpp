#include "Application.h"
#include "ModuleResourceManager.h"
#include "Resource.h"
#include "ResourceMesh.h"
#include "ResourceMaterial.h"
#include <ctime>


ModuleResourceManager::ModuleResourceManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleResourceManager::~ModuleResourceManager()
{
}

bool ModuleResourceManager::Start()
{
	App->file_system->DiscoverFiles("Models/", mesh_files, mesh_dirs);
	App->file_system->DiscoverFiles("textures/", material_files, material_dirs);
	App->file_system->DiscoverFiles(LIBRARY_MESH_FOLDER, library_mesh_files, library_mesh_dirs);
	App->file_system->DiscoverFiles(LIBRARY_TEXTURES_FOLDER, library_material_files, library_material_dirs);

	for (std::vector<std::string>::iterator i = library_mesh_files.begin(); i != library_mesh_files.end(); i++)
	{
		(*i) = LIBRARY_MESH_FOLDER + (*i);
		App->file_system->Remove((*i).c_str());
	}

	for (std::vector<std::string>::iterator i = library_material_files.begin(); i != library_material_files.end(); i++)
	{
		(*i) = LIBRARY_TEXTURES_FOLDER + (*i);
		App->file_system->Remove((*i).c_str());
	}

	for (std::vector<string>::iterator i = mesh_files.begin(); i != mesh_files.end(); i++) 
	{
		LOG("mesh detected: %s", (*i).c_str());
	}

	for (std::vector<string>::iterator i = material_files.begin(); i != material_files.end(); i++)
	{
		LOG("material detected: %s", (*i).c_str());
	}

	for (std::vector<string>::iterator i = library_mesh_files.begin(); i != library_mesh_files.end(); i++)
	{
		LOG("mesh resource detected: %s", (*i).c_str());
	}

	for (std::vector<string>::iterator i = library_material_files.begin(); i != library_material_files.end(); i++)
	{
		LOG("material resource detected: %s", (*i).c_str());
	}

	GenerateMissingMetas();

	GenerateLibaryResources();

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

uint ModuleResourceManager::GenerateTimeStamp()
{
	std::time_t time_stamp = std::time(0);

	return time_stamp;
}

Resource* ModuleResourceManager::RequestResource(uint uuid)
{
	std::map<uint, Resource*>::iterator i = resources.find(uuid);

	if (i != resources.end())
		return i->second;
	else
		return nullptr;
}

Resource* ModuleResourceManager::CreateNewResource(RESOURCE_TYPE type, uint uuid, std::string meta_path)
{
	Resource* ret = nullptr;

	switch (type) 
	{
	case RESOURCE_MESH:
		ret = new Resource(uuid, type);
		ret->resource_mesh = new ResourceMesh(uuid, meta_path, ret);
		break;
	case RESOURCE_MATERIAL:
		ret = new Resource(uuid, type);
		ret->resource_material = new ResourceMaterial(uuid, meta_path, ret);
		break;
	}

	if (ret != nullptr) 
	{
		resources.insert({ uuid, ret });
	}

	return ret;
}

void ModuleResourceManager::GenerateMeta(const char* path, RESOURCE_TYPE type)
{
	std::string meta_path = path;
	meta_path = meta_path + ".meta";

	uint uuid = GenerateNewUUID();

	uint time_stamp = GenerateTimeStamp();

	if (!App->file_system->Exists(meta_path.c_str())) 
	{

		LOG("Generating metafile from: %s", path);

		JSON_Value* root = json_value_init_object();
		JSON_Object* obj = json_value_get_object(root);

		json_object_set_number(obj, "Type", type);
		json_object_set_number(obj, "UUID", uuid); //TODO set correct uuid --> done
		json_object_set_number(obj, "Time", time_stamp); //TODO set correct time --> done

		json_serialize_to_file_pretty(root, meta_path.c_str());
		json_value_free(root);
	}
	else 
	{
		LOG("NOT Generating Metafile: %s already exists", meta_path.c_str());
	}
}

void ModuleResourceManager::GenerateMissingMetas()
{
	for (int i = 0; i < mesh_files.size(); i++) 
	{
		std::string mesh_path = mesh_files.at(i);
		mesh_path = "Models/" + mesh_path;
		
		GenerateMeta(mesh_path.c_str(), RESOURCE_TYPE::RESOURCE_MESH);			
	}

	for (int j = 0; j < material_files.size(); j++) 
	{
		std::string material_path = material_files.at(j);
		material_path = "textures/" + material_path;

		GenerateMeta(material_path.c_str(), RESOURCE_TYPE::RESOURCE_MATERIAL);
	}
}

void ModuleResourceManager::GenerateLibaryResources()
{
	for (std::vector<string>::iterator i = mesh_files.begin(); i != mesh_files.end(); i++) 
	{
		uint meta_uuid;

		std::string path;
		path = "Models/" + (*i) + ".meta";
		JSON_Value* value = json_parse_file(path.c_str());
		JSON_Object* obj = json_value_get_object(value);

		meta_uuid = json_object_get_number(obj, "UUID");

		bool resource_exists = false;

		for (std::vector<string>::iterator j = library_mesh_files.begin(); j != library_mesh_files.end(); j++) 
		{
			std::string s_uuid;
			std::string::size_type const p((*j).find_last_of('.'));
			s_uuid = (*j).substr(0, p);
			std::string uuid = to_string(meta_uuid);

			if (s_uuid == uuid)
			{
				resource_exists = true;
			}
		}

		if (!resource_exists)
		{
			CreateNewResource(RESOURCE_TYPE::RESOURCE_MESH, meta_uuid, path);
		}
	}
}





