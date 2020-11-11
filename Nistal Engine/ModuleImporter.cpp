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

bool ModuleImporter::CleanUp()
{
	bool ret = true;

	return ret;
}


bool ModuleImporter::SaveData(modelData model, string file_name)
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

	char* fileBuffer = new char[generalSize];
	char* cursor = fileBuffer;


	//saving the header
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
	string path_to_save(LIBRARY_MESH_FOLDER + string(file_name) + string(".mesh"));
	App->file_system->Save(path_to_save.c_str(), fileBuffer, generalSize);

	return ret;
}

bool ModuleImporter::LoadData()
{
	bool ret = true;

	return ret;
}