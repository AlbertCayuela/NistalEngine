#include "Application.h"
#include "ModuleLoadFBX.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Glew/include/glew.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")


ModuleLoadFBX::ModuleLoadFBX(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleLoadFBX::~ModuleLoadFBX()
{
}

bool ModuleLoadFBX::Start()
{
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);
    model_node = json_object_dotget_object(App->config, "Model");
    path = json_object_get_string(model_node, "Path");

	return true;
}

update_status ModuleLoadFBX::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleLoadFBX::Update(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleLoadFBX::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleLoadFBX::CleanUp()
{
	aiDetachAllLogStreams();

	return true;
}

bool ModuleLoadFBX::LoadFBX(const char* file_path)
{
    //LOADING FBX --------------------------------------------------
    const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);

    if (scene != nullptr && scene->HasMeshes())
    {
        for (uint i = 0; i < scene->mNumMeshes; i++)
        {
            mesh = scene->mMeshes[i];
            model.num_vertex = mesh->mNumVertices;
            model.vertex = new float[mesh->mNumVertices * 3];
            memcpy(model.vertex, mesh->mVertices, sizeof(float) * model.num_vertex * 3);
            LOG("New mesh with %d vertices", model.num_vertex);

            if (mesh->HasFaces())
            {
                model.num_index = mesh->mNumFaces * 3;
                model.index = new uint[model.num_index]; //assume each face is a triangle
                for (uint i = 0; i < mesh->mNumFaces; i++)
                {
                    if (mesh->mFaces[i].mNumIndices != 3)
                    {
                        LOG("WARNING, geometry face with != 3 indices!");
                    }
                    else
                        //not sure if it's "mesh" at mesh->mFaces[i].mIndices, hmm (it supposed to be a new mesh)
                        memcpy(&model.index[i * 3], mesh->mFaces[i].mIndices, 3 * sizeof(uint));
                }
            }
        }
        aiReleaseImport(scene);
        glGenBuffers(1, (GLuint*)&(model.id_vertex));
        glBindBuffer(GL_ARRAY_BUFFER, model.id_vertex);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * model.num_vertex, model.vertex, GL_STATIC_DRAW);

        glGenBuffers(1, (GLuint*)&(model.id_index));
        glBindBuffer(GL_ARRAY_BUFFER, model.id_index);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * model.num_index, model.index, GL_STATIC_DRAW);

        glEnableClientState(GL_VERTEX_ARRAY);

        glBindBuffer(GL_ARRAY_BUFFER, model.id_vertex);
        glVertexPointer(3, GL_FLOAT, 0, NULL);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.id_index);
        glDrawElements(GL_TRIANGLES, model.num_index, GL_UNSIGNED_INT, NULL);

        glDisableClientState(GL_VERTEX_ARRAY);



    }
    else 
    {
        LOG("Error loading scene %s", path);
        
        return false;
    }
        

    //--------------------------------------------------------------
}
