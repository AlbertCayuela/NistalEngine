#include "Application.h"
#include "ModuleLoadFBX.h"

#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Devil/include/il.h"
#include "Devil/include/ilu.h"
#include "Devil/include/ilut.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")
#pragma comment (lib, "Devil/libx86/DevIL.lib")
#pragma comment (lib, "Devil/libx86/ILU.lib")
#pragma comment (lib, "Devil/libx86/ILUT.lib")



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

    LoadTexture("Textures/Baker_house.png");

	return true;
}

update_status ModuleLoadFBX::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleLoadFBX::Update(float dt)
{
    if (!all_fbx_loaded)
    {
        App->load_fbx->LoadFBX(path);
        all_fbx_loaded = true;
    }

    //draw every mesh
    for (std::vector<modelData>::iterator i = App->load_fbx->meshes.begin(); i != App->load_fbx->meshes.end(); ++i)
    {
        App->load_fbx->DrawFBX(*i);
    }

    //DrawFBX(model);

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
    scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);

    if (scene != nullptr && scene->HasMeshes())
        LoadMeshes(scene, App->scene_intro->root);
    else 
    {
        LOG("Error loading scene %s", path);
        return false;
    }
}

void ModuleLoadFBX::LoadMeshes(const aiScene* scene, GameObject* game_object)
{
    for (uint i = 0; i < scene->mNumMeshes; ++i)
    {
        //loading vertices
        //GameObject* new_object = App->scene_intro->CreateGameObject(game_object);

        mesh = scene->mMeshes[i];
        model = modelData();
        model.num_vertex = mesh->mNumVertices;
        model.vertices = new float[mesh->mNumVertices * 3];
        memcpy(model.vertices, mesh->mVertices, sizeof(float) * model.num_vertex * 3);

        //loading indices
        if (mesh->HasFaces())
        {
            LoadIndices(mesh);
        }
        if (mesh->HasTextureCoords(model.id_uvs))
        {
            //UVs
            model.num_uvs = mesh->mNumVertices;
            model.uvs = new  float[model.num_uvs * 2];

            for (int i = 0; i < mesh->mNumVertices; ++i)
            {
                memcpy(&model.uvs[i * 2], &mesh->mTextureCoords[0][i].x, sizeof(float));
                memcpy(&model.uvs[(i * 2) + 1], &mesh->mTextureCoords[0][i].y, sizeof(float));
            }
        }
        if (mesh->HasNormals())
        {
            model.normals = new aiVector3D[mesh->mNumVertices];
            memcpy(model.normals, mesh->mNormals, sizeof(aiVector3D) * mesh->mNumVertices);
        }

        //loading uvs
        //model.num_uvs_channels = mesh->GetNumUVChannels();
        //if (model.num_uvs_channels > 0)
        //{
        //    App->texture->LoadUVs(&model, mesh);
        //}

        //if (scene->HasMaterials())
        //{
        //    App->texture->LoadMaterials(scene, mesh, &model);
        //}

        //loading normals
        model.num_faces = mesh->mNumFaces;
        model.faces_normals = new float3[mesh->mNumFaces];
        model.face_middle = new float3[mesh->mNumFaces];

        for (uint i = 0; i < model.num_index; i += 3)
        {
            uint index = model.indices[i];
            float3 vertex1 = { model.vertices[index * 3], model.vertices[index * 3 + 1] , model.vertices[index * 3 + 2] };
            index = model.indices[i + 1];

            float3 vertex2 = { model.vertices[index * 3], model.vertices[index * 3 + 1] , model.vertices[index * 3 + 2] };
            index = model.indices[i + 2];

            float3 vertex3 = { model.vertices[index * 3], model.vertices[index * 3 + 1] , model.vertices[index * 3 + 2] };

            float3 vector1 = vertex2 - vertex1;
            float3 vector2 = vertex3 - vertex1;

            model.faces_normals[i / 3] = Cross(vector1, vector2);
            model.faces_normals[i / 3].Normalize();
            model.face_middle[i / 3] = { (vertex1.x + vertex2.x + vertex3.x) / 3, (vertex1.y + vertex2.y + vertex3.y) / 3, (vertex1.z + vertex2.z + vertex3.z) / 3 };
        }  

        AddBuffers();

        meshes.push_back(model);

        LOG("Loaded mesh with %i vertices.", model.num_vertex);
        LOG("Loaded mesh with %i indices.", model.num_index);
        LOG("Loaded mesh with %i triangles.", model.num_vertex / 3);
        LOG("Loaded mesh with %i normals.", model.num_normals);
        LOG("Loaded mesh with %i uvs.", model.num_uvs);
    }

}

void ModuleLoadFBX::DrawFBX(modelData model)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    //change color viewport
    //glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

    //bind texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    //bind vertices
    glBindBuffer(GL_ARRAY_BUFFER, model.id_vertex);
    glVertexPointer(3, GL_FLOAT, 0, NULL);

    //bind uvs
    glBindBuffer(GL_ARRAY_BUFFER, model.id_uvs);
    glTexCoordPointer(2, GL_FLOAT, 0, NULL);

    //bind indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.id_index);

    //Draw
    glDrawElements(GL_TRIANGLES, model.num_index, GL_UNSIGNED_INT, NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void ModuleLoadFBX::DrawNormals(modelData model)
{
    glColor3f(0, 1, 0.77f);
    float lenght = 0.5f;

    for (uint i = 0; i < mesh->mNumFaces; i++)
    {
        glBegin(GL_LINES);
        glVertex3f(model.face_middle [i].x, model.face_middle[i].y, model.face_middle[i].z);
        glVertex3f(model.face_middle[i].x + model.faces_normals[i].x * lenght, model.face_middle[i].y + model.faces_normals[i].y * lenght, model.face_middle[i].z + model.faces_normals[i].z * lenght);
        glEnd();
    }

    glColor3f(1, 1, 1);    
}

void ModuleLoadFBX::DrawVertexNormals(modelData model)
{
    glColor3f(1.0f, 0.0f, 0.0f);
    uint j = 0;
    float lenght = 0.5f;
    for (uint i = 0; i < model.num_vertex * 3; i += 3)
    {
        glBegin(GL_LINES);
        glVertex3f(model.vertices[i], model.vertices[i + 1], model.vertices[i + 2]);
        glVertex3f(model.vertices[i] + model.normals[j].x * lenght, model.vertices[i + 1] + model.normals[j].y * lenght, model.vertices[i + 2] + model.normals[j].z * lenght);
        ++j;
        glEnd();
    }
    glColor3f(1, 1, 1);
}

void ModuleLoadFBX::AddBuffers()
{
    glGenBuffers(1, &(model.id_vertex));
    glBindBuffer(GL_ARRAY_BUFFER, model.id_vertex);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * model.num_vertex, model.vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &(model.id_index));
    glBindBuffer(GL_ARRAY_BUFFER, model.id_index);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * model.num_index, model.indices, GL_STATIC_DRAW);

    glGenBuffers(1, &(model.id_normals));
    glBindBuffer(GL_ARRAY_BUFFER, model.id_normals);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * model.num_normals, model.normals, GL_STATIC_DRAW);

    glGenBuffers(1, &(model.id_uvs));
    glBindBuffer(GL_ARRAY_BUFFER, model.id_uvs);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * model.num_uvs * 2, model.uvs, GL_STATIC_DRAW);
}

void ModuleLoadFBX::LoadIndices(aiMesh* mesh)
{
    model.num_index = mesh->mNumFaces * 3;
    model.indices = new uint[model.num_index]; //assume each face is a triangle
    for (uint i = 0; i < mesh->mNumFaces; i++)
    {
        if (mesh->mFaces[i].mNumIndices != 3)
        {
            LOG("WARNING, geometry face with != 3 indices!");
        }
        else
        {
            memcpy(&model.indices[i * 3], mesh->mFaces[i].mIndices, 3 * sizeof(uint));
        }
    }
}

void ModuleLoadFBX::LoadTexture(char* texture_path) 
{
    ilInit();
    iluInit();
    ilutInit();

    if (ilLoadImage(texture_path))
    {
        uint id = 0;

        ilGenImages(1, &id);
        ilBindImage(id);
        ilLoadImage(texture_path);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        texture_id = ilutGLBindTexImage();
        glBindTexture(GL_TEXTURE_2D, 0);
        ilDeleteImages(1, &id);
        LOG("TEXTURE CORRECTLY LOADED");
    }
    else
    {
        LOG("ERROR LOADING TEXTURE");
    }
}
