#include "Application.h"
#include "ModuleLoadFBX.h"
#include "GameObject.h"
#include "GOMesh.h"
#include "GOMaterial.h"
#include "GOTransform.h"
#include "ResourceMesh.h"
#include "ModuleImporter.h"

#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cimport.h"

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
    texture_node = json_object_dotget_object(App->config, "Texture");

    model_path = json_object_get_string(model_node, "Path");
    texture_path = json_object_get_string(texture_node, "Texture Path");

    ilInit();
    iluInit();
    ilutInit();

	return true;
}

update_status ModuleLoadFBX::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleLoadFBX::Update(float dt)
{
    if (App->input->GetKey(SDL_SCANCODE_U) == KEY_REPEAT)
    {
        Unparent();
    }

    if (App->input->GetKey(SDL_SCANCODE_P) == KEY_REPEAT && !parent)
    {
        LOG("Parent GO");

        for (std::vector<GameObject*>::iterator i = App->scene_intro->game_objects.begin(); i != App->scene_intro->game_objects.end(); ++i)
        {
            if ((*i) == App->scene_intro->selected_go)
            {
                parent = true;
                new_parent = (*i);
            }
        }
    }

    if (App->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT && parent)
    {
        for (std::vector<GameObject*>::iterator i = App->scene_intro->game_objects.begin(); i != App->scene_intro->game_objects.end(); ++i)
        {
            if ((*i) == App->scene_intro->selected_go)
            {
                (*i)->parent = new_parent;
                parent = false;
            }
        }
    }

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

bool ModuleLoadFBX::LoadFBX(const char* file_path, GameObject* parent)
{
    //LOADING FBX --------------------------------------------------
    scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);

    aiNode* root_node = scene->mRootNode;

    //TODO: loading street (fixing)
    //create game object for every node
    //set transform from node (info de los verdes esos :) )

    if (scene != nullptr && scene->HasMeshes())
    {
        if (parent == nullptr) 
        {
            for(int i=0; i<root_node->mNumChildren; ++i)
                LoadMeshes(scene, root_node->mChildren[i], App->scene_intro->root, file_path);
        }        
        else if (parent != nullptr)
        {
            for (int i = 0; i < root_node->mNumChildren; ++i)
                LoadMeshes(scene, root_node->mChildren[i], parent, file_path);
        }
    }
    else 
    {
        LOG("Error loading scene %s", model_path);
        return false;
    }
}

void ModuleLoadFBX::LoadMeshes(const aiScene* scene,aiNode* node, GameObject* game_object, const char* file_path)
{
    if (node->mNumMeshes > 0) 
    {
        mesh = scene->mMeshes[node->mMeshes[0]];
        model = modelData();
        go_name = node->mName.C_Str();
        new_go = App->scene_intro->CreateGameObject(game_object, go_name.c_str());

        //imported_meshes.push_back(go_name);

        //LOADING MATERIAL
        LoadMaterial(new_go);
       
        //TODO: Watch out Memory Leaks. When we will be able to delete models, check if everything is deleted. Otherwise, it will cause memory leaks :)
        LoadVertices();

        //LOADING FACES
        if (mesh->HasFaces())
        {
            LoadIndices(mesh);
        }

        //LOADING TEXTURE COORDS
        //UVs
        //In case that we load a texture without create the UVs buffer, imgui crashes :D. So it's because of that we create the buffer outside the if. That way there's at least one empty UVs buffer
        //that picks and uses the first texture pixel

        model.num_uvs = mesh->mNumVertices;
        model.uvs = new float[model.num_uvs * 2];

        if (mesh->HasTextureCoords(model.id_uvs))
        {
            for (int i = 0; i < mesh->mNumVertices; ++i)
            {
                memcpy(&model.uvs[i * 2], &mesh->mTextureCoords[0][i].x, sizeof(float));
                memcpy(&model.uvs[(i * 2) + 1], &mesh->mTextureCoords[0][i].y, sizeof(float));
            }
        }

        //LOADING NORMALS
        if (mesh->HasNormals())
        {
            model.normals = new aiVector3D[mesh->mNumVertices];
            memcpy(model.normals, mesh->mNormals, sizeof(aiVector3D) * mesh->mNumVertices);
        }

        //---------------------------------------------------------------------------

        //loading normals
        /*model.num_faces = mesh->mNumFaces;
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
        }  */

        //NumUVsChannel
        model.nums_uvs_channels = mesh->GetNumUVChannels();

        AddBuffers();

        //LOADING TRANSFORM
        aiVector3D translation, scaling, rot_euler;
        aiQuaternion rotation;
        node->mTransformation.Decompose(scaling, rotation, translation);
        aiMatrix3x3 rot_mat = rotation.GetMatrix();
        rot_euler = rot_mat.GetEuler();

        float3 pos(translation.x, translation.y, translation.z);
        float3 scale(scaling.x, scaling.y, scaling.z);
        Quat rot(rotation.x, rotation.y, rotation.z, rotation.w);

        uint resource_uuid = App->resource_manager->GenerateNewUUID();

        new_resource = App->resource_manager->CreateNewResource(RESOURCE_TYPE::RESOURCE_MESH, resource_uuid, "");

        new_go->AddComponent(GOCOMPONENT_TYPE::MESH, "mesh");
        new_go->mesh->mesh_uuid = new_resource->uuid;

        new_resource->resource_mesh->model_info = model;
        new_go->mesh->mesh_info = model;

        new_go->transform->position = pos;
        new_go->transform->rotation = rot;
        new_go->transform->scale = scale;

        //---------------------------------------------------------------------------

        App->importer->SaveOwnFormat(model, to_string(new_resource->uuid));
        
  
        //OUTPUT
        LOG("Loaded mesh with %i vertices.", model.num_vertex);
        LOG("Loaded mesh with %i indices.", model.num_index);
        LOG("Loaded mesh with %i triangles.", model.num_vertex / 3);
        LOG("Loaded mesh with %i normals.", model.num_normals);
        LOG("Loaded mesh with %i uvs.", model.num_uvs);
    } 


    for (int i = 0; i < node->mNumChildren; ++i)
        LoadMeshes(scene, node->mChildren[i], game_object, file_path);
}

void ModuleLoadFBX::DrawNormals(modelData model)
{
    glColor3f(0, 1, 0.77f);
    float lenght = 0.5f;

    for (uint i = 0; i < model.num_faces; i++)
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
    model.indices = new uint[model.num_index];
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

void ModuleLoadFBX::LoadTexture(const char* texture_path) 
{
    if (ilLoadImage(texture_path))
    {
        texture_width = ilGetInteger(IL_IMAGE_WIDTH);
        texture_height = ilGetInteger(IL_IMAGE_HEIGHT);

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

void ModuleLoadFBX::LoadMaterial(GameObject* game_object)
{
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    if (material != nullptr)
    {
        textures_num = material->GetTextureCount(aiTextureType_DIFFUSE);
        aiString tex_path;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &tex_path);
        std::string texture_path;
        texture_path = tex_path.data;
        LOG("Texture detected: %s", texture_path.c_str());
        App->importer->TextureSaving(texture_path, "textures/");
        game_object->AddComponent(GOCOMPONENT_TYPE::MATERIAL, texture_path.c_str());
        game_object->material->GetNewMaterial(texture_path);
    }
}

void ModuleLoadFBX::LoadVertices()
{
    model.num_vertex = mesh->mNumVertices;
    model.vertices = new float[mesh->mNumVertices * 3];
    memcpy(model.vertices, mesh->mVertices, sizeof(float) * model.num_vertex * 3);
}

void ModuleLoadFBX::Unparent()
{
    LOG("Reparent to root");
    App->scene_intro->selected_go->parent->active = false;

    for (std::vector<GameObject*>::iterator i = App->scene_intro->game_objects.begin(); i != App->scene_intro->game_objects.end(); ++i)
    {
        if ((*i) == App->scene_intro->selected_go)
        {
            (*i)->parent = App->scene_intro->root;
        }
    }

    for (std::vector<GameObject*>::iterator i = App->scene_intro->own_game_objects.begin(); i != App->scene_intro->own_game_objects.end(); ++i)
    {
        if ((*i) == App->scene_intro->selected_go)
        {
            (*i)->parent = App->scene_intro->root;
        }
    }
}
