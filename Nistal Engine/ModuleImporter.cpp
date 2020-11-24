#include "Application.h"
#include "ModuleImporter.h"
#include "ModuleFS.h"
#include "GOTransform.h"
#include "GOMaterial.h"
#include "GOMesh.h"

//TODO: Check this libraries
//#include "Devil/include/config.h"
#include "Devil/include/il.h"

ModuleImporter::ModuleImporter(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleImporter::~ModuleImporter()
{}

bool ModuleImporter::Start()
{
	bool ret = true;

	return ret;
}

bool ModuleImporter::Update()
{
	bool ret = true;

	return ret;
}

bool ModuleImporter::CleanUp()
{
	bool ret = true;

	return ret;
}


bool ModuleImporter::SaveOwnFormat(modelData model, string name_to_file)
{
	bool ret = true;
	//save each mesh component as .material, .mesh, .model, etc

	//in the same order when we create the buffers in AddBuffers() :
	uint header[4] = { model.num_vertex, model.num_index, model.num_normals, model.num_uvs};
	uint generalSize = sizeof(header) +
		sizeof(float) * 3 * model.num_vertex +
		sizeof(float) * model.num_index +
		sizeof(float) * 3 * model.num_normals +
		sizeof(float) * model.num_uvs * 2;

	char* data = new char[generalSize];
	char* cursor = data;


	//saving header
	uint bytes = sizeof(header);
	memcpy(cursor, header, bytes);
	cursor += bytes;

	//saving data
	bytes = sizeof(float) * model.num_vertex * 3;
	memcpy(cursor, model.vertices, bytes);
	cursor += bytes;

	bytes = sizeof(float) * model.num_index;
	memcpy(cursor, model.indices, bytes);
	cursor += bytes;

	bytes = sizeof(float) * model.num_normals * 3;
	memcpy(cursor, model.normals, bytes);
	cursor += bytes;

	bytes = sizeof(float) * model.num_uvs * 2;
	memcpy(cursor, model.uvs, bytes);
	cursor += bytes;

	//file system
	string path_to_save(LIBRARY_MESH_FOLDER + string(name_to_file) + string(".mesh"));
	App->file_system->Save(path_to_save.c_str(), data, generalSize);

	LOG("Saving own format gameobject: %s", name_to_file.c_str());

	return ret;
}

bool ModuleImporter::LoadOwnFormat(string file_name)
{
	bool ret = true;

	string full_path(LIBRARY_MESH_FOLDER + string(file_name) + string(".mesh"));
	string name;
	App->file_system->SplitFilePath(file_name.c_str(), nullptr, &name);
	if (createOwnGameObject)
	{
		new_go = App->scene_intro->CreateOWNGameObject(App->scene_intro->root, name.c_str());
		new_go->AddComponent(GOCOMPONENT_TYPE::MESH, "ownMesh");
	}
	createOwnGameObject = false;

	char* data;
	App->file_system->Load(full_path.c_str(), &data);
	char* cursor = data;

	//loading header
	uint header[4] = { 0u, 0u, 0u, 0u };
	uint bytes = sizeof(header);
	memcpy(header, cursor, bytes);
	cursor += bytes;

	new_go->mesh->mesh_info.num_vertex = header[0];
	new_go->mesh->mesh_info.num_index = header[1];
	new_go->mesh->mesh_info.num_normals = header[2];
	new_go->mesh->mesh_info.num_uvs = header[3];

	//loading data
	bytes = sizeof(float) * new_go->mesh->mesh_info.num_vertex * 3;
	new_go->mesh->mesh_info.vertices = new float[new_go->mesh->mesh_info.num_vertex * 3];
	memcpy(new_go->mesh->mesh_info.vertices, cursor, bytes);
	cursor += bytes;
	LOG("OwnFormat num_vertex: %i", new_go->mesh->mesh_info.num_vertex);
	

	bytes = sizeof(float) * new_go->mesh->mesh_info.num_index;
	new_go->mesh->mesh_info.indices = new uint[new_go->mesh->mesh_info.num_index];
	memcpy(new_go->mesh->mesh_info.indices, cursor, bytes);
	cursor += bytes;
	LOG("OwnFormat num_index: %i", new_go->mesh->mesh_info.num_index);

	bytes = sizeof(float) * new_go->mesh->mesh_info.num_normals * 3;
	new_go->mesh->mesh_info.normals = new aiVector3D[new_go->mesh->mesh_info.num_normals * 3];
	memcpy(new_go->mesh->mesh_info.normals, cursor, bytes);
	cursor += bytes;
	LOG("OwnFormat num_normals: %i", new_go->mesh->mesh_info.num_normals);

	bytes = sizeof(float) * new_go->mesh->mesh_info.num_uvs * 2;
	new_go->mesh->mesh_info.uvs = new float[new_go->mesh->mesh_info.num_uvs * 2];
	memcpy(new_go->mesh->mesh_info.uvs, cursor, bytes);
	cursor += bytes;
	LOG("OwnFormat num_uvs: %i", new_go->mesh->mesh_info.num_uvs);

	//Adding buffers for our Own Meshes (.mesh files)
	glGenBuffers(1, &(new_go->mesh->mesh_info.id_vertex));
	glBindBuffer(GL_ARRAY_BUFFER, new_go->mesh->mesh_info.id_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * new_go->mesh->mesh_info.num_vertex, new_go->mesh->mesh_info.vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &(new_go->mesh->mesh_info.id_index));
	glBindBuffer(GL_ARRAY_BUFFER, new_go->mesh->mesh_info.id_index);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * new_go->mesh->mesh_info.num_index, new_go->mesh->mesh_info.indices, GL_STATIC_DRAW);

	glGenBuffers(1, &(new_go->mesh->mesh_info.id_normals));
	glBindBuffer(GL_ARRAY_BUFFER, new_go->mesh->mesh_info.id_normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * new_go->mesh->mesh_info.num_normals, new_go->mesh->mesh_info.normals, GL_STATIC_DRAW);

	glGenBuffers(1, &(new_go->mesh->mesh_info.id_uvs));
	glBindBuffer(GL_ARRAY_BUFFER, new_go->mesh->mesh_info.id_uvs);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * new_go->mesh->mesh_info.num_uvs * 2, new_go->mesh->mesh_info.uvs, GL_STATIC_DRAW);

	return ret;
}



bool ModuleImporter::TextureSaving(string texture_name)
{
	bool ret = true;

	LOG("Importing texture: %s", texture_name.c_str());
	std::string file_name = texture_name;
	LOG("file name: %s", file_name.c_str());
	std::string name_texture = file_name.substr(file_name.find_last_of("\\") + 1);
	LOG("texture name: %s", name_texture.c_str());
	std::string::size_type const p(name_texture.find_last_of('.'));
	std::string texture_ui_name = name_texture.substr(0, p);
	LOG("texture name without extension: %s", texture_ui_name.c_str());

	ILuint size;
	char* data;

	//char* fileBuffer = nullptr;

	ilSetInteger(IL_DXTC_FORMAT, IL_DXT5);
	size = ilSaveL(IL_DDS, NULL, 0);

	//fileBuffer = new char[size];

	if (size > 0)
	{
		data = new char[size]; //allocate data buffer
		if (ilSaveL(IL_DDS, data, size) > 0)
		{
			std:string output_file;
			//Save custom format
			//string path_to_save(LIBRARY_TEXTURES_FOLDER + string(texture_name) + string(".dds"));
			//fileBuffer = (char*)data;
			ret = App->file_system->SaveUnique(output_file, data, size, LIBRARY_TEXTURES_FOLDER, texture_ui_name.c_str(), "dds");

			LOG("Output texture name: %s", output_file.c_str());
		}
	
		delete[] data;
	}

	return ret;
}