#include "Application.h"
#include "ModuleLoadFBX.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
//#include "Glew/include/glew.h"
#include "Devil/include/il.h"
#include "Devil/include/ilu.h"
#include "Devil/include/ilut.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")
#pragma comment (lib, "Devil/libx86/DevIL.lib")
#pragma comment (lib, "Devil/libx86/ILU.lib")
#pragma comment (lib, "Devil/libx86/ILUT.lib")

#include "Texture.h"



ModuleLoadFBX::ModuleLoadFBX(Application* app, bool start_enabled) : Module(app, start_enabled)
{
    ilInit();
    iluInit();
    ilutInit();
    ilutRenderer(ILUT_OPENGL);
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
    texture_path = json_object_get_string(model_node, "Texture Path");

    //LoadFBX(path);

    //TEXTURES
    
    bool testing = ilLoadImage("Textures/lenna.png");
    int width = ilGetInteger(IL_IMAGE_WIDTH);
    int height = ilGetInteger(IL_IMAGE_HEIGHT);
    //ilutRenderer(ILUT_OPENGL);

    texture = ilutGLBindTexImage(); //this line changes the color environment to 1 pixel color of Lenna
    glBindTexture(GL_TEXTURE_2D, texture);
    if (testing) {
        LOG("LENNA LOADED");
    }
    else {
        LOG("LENNA NOT LOADED");
    }

	return true;
}

update_status ModuleLoadFBX::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleLoadFBX::Update(float dt)
{
    //Draw texture

	return UPDATE_CONTINUE;
}

update_status ModuleLoadFBX::PostUpdate(float dt)
{
    //DrawFBX(model);

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
        LoadMeshes(scene);
    else 
    {
        LOG("Error loading scene %s", path);
        return false;
    }
        

    //--------------------------------------------------------------
}

void ModuleLoadFBX::LoadMeshes(const aiScene* scene)
{
    for (uint i = 0; i < scene->mNumMeshes; i++)
    {
        //loading vertices
        mesh = scene->mMeshes[i];
        model.num_vertex = mesh->mNumVertices;
        model.vertices = new float[mesh->mNumVertices * 3];
        memcpy(model.vertices, mesh->mVertices, sizeof(float) * model.num_vertex * 3);
        LOG("New mesh with %d vertices", model.num_vertex);

        if (mesh->HasFaces())
        {
            LoadIndices(mesh);
        }
        if (mesh->HasNormals())
        {
            model.normals = new aiVector3D[mesh->mNumVertices];
            memcpy(model.normals, mesh->mNormals, sizeof(aiVector3D) * mesh->mNumVertices);
        }

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
    
        //loading textures
        if (mesh->HasTextureCoords(0))
        {
            model.num_uv_components = mesh->mNumUVComponents[0];
            if (model.num_uv_components == 2)
            {
                model.uv_coord = new float[model.num_vertex * model.num_uv_components];
                for (uint i = 0; i < model.num_vertex; i++)
                {
                    memcpy(&model.uv_coord[i * model.num_uv_components], &mesh->mTextureCoords[0][i], sizeof(float*) * model.num_uv_components);
                }
            }
        }
    
    }

    AddFBX(); //Creates buffers
    //aiReleaseImport(scene);
}

void ModuleLoadFBX::DrawFBX(modelData model)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, model.id_vertex);
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.id_index);
    glDrawElements(GL_TRIANGLES, model.num_index, GL_UNSIGNED_INT, NULL);
    glDisableClientState(GL_VERTEX_ARRAY);
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

/*void ModuleLoadFBX::DrawTexture(modelData model)
{
    glGenBuffers(1, &model.id_vertex);
    glBindBuffer(GL_ARRAY_BUFFER, model.id_vertex);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * model.num_vertex * 3, model.vertices, GL_STATIC_DRAW);

    if (model.num_faces > 0)
    {
        glGenBuffers(1, &model.id_index);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.id_index);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * model.num_faces * 3, model.indices, GL_STATIC_DRAW);
    }

    if (model.uv_coord > 0)
    {
        glGenBuffers(1, &model.id_uv);
        glBindBuffer(GL_ARRAY_BUFFER, model.id_uv);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * model.num_uv_components * model.num_vertex, &model.uv_coord[0], GL_STATIC_DRAW);
    }
}*/

Texture* ModuleLoadFBX::LoadTexture(const char* path)
{
    Texture* new_texture = nullptr;

    if (path != nullptr && path != "")
    {
        uint devil_id = 0;
        ilGenImages(1, &devil_id);
        ilBindImage(devil_id);
        ilutRenderer(ILUT_OPENGL);

        if (!ilLoad(IL_PNG, path))
        {
            auto error = ilGetError();
            LOG("Error while loading texting with path: %s. Error: %s", path, ilGetString(error));
            return new_texture;
        }
        else
        {
            new_texture = new Texture();
            new_texture->buffer_id = ilutGLBindTexImage();
            new_texture->height = ilGetInteger(IL_IMAGE_HEIGHT);
            new_texture->width = ilGetInteger(IL_IMAGE_WIDTH);

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glBindTexture(GL_TEXTURE_2D, new_texture->buffer_id);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, 0x8072, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

            textures[path] = new_texture;
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        
        ilDeleteImages(1, &devil_id);
    }

    else
    {
        LOG("There's no path");
    }

    return new_texture;
}

void ModuleLoadFBX::AddFBX()
{
    glGenBuffers(1, (GLuint*)&(model.id_vertex));
    glBindBuffer(GL_ARRAY_BUFFER, model.id_vertex);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * model.num_vertex, model.vertices, GL_STATIC_DRAW);

    glGenBuffers(1, (GLuint*)&(model.id_index));
    glBindBuffer(GL_ARRAY_BUFFER, model.id_index);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * model.num_index, model.indices, GL_STATIC_DRAW);
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
            //not sure if it's "mesh" at mesh->mFaces[i].mIndices, hmm (it supposed to be a new mesh)
            memcpy(&model.indices[i * 3], mesh->mFaces[i].mIndices, 3 * sizeof(uint));

        }
    }
}