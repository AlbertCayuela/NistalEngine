#include "Application.h"
#include "ModuleImporter.h"
#include "ModuleFS.h"

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

	return ret;
}

bool ModuleImporter::LoadOwnFormat(string file_name)
{
	bool ret = true;

	string full_path(LIBRARY_MESH_FOLDER + string(file_name) + string(".mesh"));
	string name;
	App->file_system->SplitFilePath(file_name.c_str(), nullptr, &name);
	GameObject* new_go = new GameObject(App->scene_intro->root, name.c_str());
	//GOComponent* mesh = (GOComponent*)new_go->AddComponent(GOCOMPONENT_TYPE::MESH);

	modelData model;

	char* data;
	App->file_system->Load(full_path.c_str(), &data);
	char* cursor = data;

	//loading header
	uint header[4] = { 0u, 0u, 0u, 0u };
	uint bytes = sizeof(header);
	memcpy(header, cursor, bytes);
	cursor += bytes;

	model.num_vertex = header[0];
	model.num_index = header[1];
	model.num_normals = header[2];
	model.num_uvs = header[3];

	//loading data
	bytes = sizeof(float) * model.num_vertex * 3;
	model.vertices = new float[model.num_vertex * 3];
	memcpy(model.vertices, cursor, bytes);
	cursor += bytes;
	LOG("OwnFormat num_vertex: %i", model.num_vertex);
	

	bytes = sizeof(float) * model.num_index;
	model.indices = new uint[model.num_index];
	memcpy(model.indices, cursor, bytes);
	cursor += bytes;
	LOG("OwnFormat num_index: %i", model.num_index);

	bytes = sizeof(float) * model.num_normals * 3;
	model.normals = new aiVector3D[model.num_normals * 3];
	memcpy(model.normals, cursor, bytes);
	cursor += bytes;
	LOG("OwnFormat num_normals: %i", model.num_normals);

	bytes = sizeof(float) * model.num_uvs * 2;
	model.uvs = new float[model.num_uvs * 2];
	memcpy(model.uvs, cursor, bytes);
	cursor += bytes;
	LOG("OwnFormat num_uvs: %i", model.num_uvs);

	return ret;
}