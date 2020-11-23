#include "Application.h"
#include "ModuleImporter.h"
#include "ModuleFS.h"
#include "GOTransform.h"
#include "GOMaterial.h"

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
	new_go = new GameObject(App->scene_intro->root, name.c_str());
	//GOComponent* mesh = (GOComponent*)new_go->AddComponent(GOCOMPONENT_TYPE::MESH);

	char* data;
	App->file_system->Load(full_path.c_str(), &data);
	char* cursor = data;

	//loading header
	uint header[4] = { 0u, 0u, 0u, 0u };
	uint bytes = sizeof(header);
	memcpy(header, cursor, bytes);
	cursor += bytes;

	modelOwnFormat.num_vertex = header[0];
	modelOwnFormat.num_index = header[1];
	modelOwnFormat.num_normals = header[2];
	modelOwnFormat.num_uvs = header[3];

	//loading data
	bytes = sizeof(float) * modelOwnFormat.num_vertex * 3;
	modelOwnFormat.vertices = new float[modelOwnFormat.num_vertex * 3];
	memcpy(modelOwnFormat.vertices, cursor, bytes);
	cursor += bytes;
	LOG("OwnFormat num_vertex: %i", modelOwnFormat.num_vertex);
	

	bytes = sizeof(float) * modelOwnFormat.num_index;
	modelOwnFormat.indices = new uint[modelOwnFormat.num_index];
	memcpy(modelOwnFormat.indices, cursor, bytes);
	cursor += bytes;
	LOG("OwnFormat num_index: %i", modelOwnFormat.num_index);

	bytes = sizeof(float) * modelOwnFormat.num_normals * 3;
	modelOwnFormat.normals = new aiVector3D[modelOwnFormat.num_normals * 3];
	memcpy(modelOwnFormat.normals, cursor, bytes);
	cursor += bytes;
	LOG("OwnFormat num_normals: %i", modelOwnFormat.num_normals);

	bytes = sizeof(float) * modelOwnFormat.num_uvs * 2;
	modelOwnFormat.uvs = new float[modelOwnFormat.num_uvs * 2];
	memcpy(modelOwnFormat.uvs, cursor, bytes);
	cursor += bytes;
	LOG("OwnFormat num_uvs: %i", modelOwnFormat.num_uvs);

	//Draw Own Format
	App->scene_intro->render_own_model = true;

	return ret;
}



bool ModuleImporter::TextureSaving(string texture_name)
{
	bool ret = true;

	ILuint size;
	ILubyte* data;

	char* fileBuffer = nullptr;

	ilSetInteger(IL_DXTC_FORMAT, IL_DXT5);
	size = ilSaveL(IL_DDS, nullptr, 0);

	fileBuffer = new char[size];

	if (size > 0)
	{
		data = new ILubyte[size]; //allocate data buffer
		if (ilSaveL(IL_DDS, data, size) > 0)
			fileBuffer = (char*)data;

		//RELEASE_ARRAY(data);
	}

	//Save custom format
	string path_to_save(LIBRARY_TEXTURES_FOLDER + string(texture_name) + string(".tex"));
	App->file_system->Save(path_to_save.c_str(), data, size);

	return ret;
}